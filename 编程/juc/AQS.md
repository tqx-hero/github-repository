### AQS

​	AbstractQueuedSynchronizer，抽象队列同步器。是所有ReentrentLock、ReentrentReadWriteLock、Condition、阻塞队列、CountDownLatch、CyclicBarrier、Semaphore等juc并发工具的底层实现框架，简称AQS。

​	AQS大体由两个重要组成部分：标识位state与双向链表组成的同步队列。

​	state：是所有juc实现能够操控同步队列的一个int类型状态，基于对该状态的CAS修改，成功后即可控制线程出队或入队。

#### ReentrentLock：

###### 	1、以ReentrentLock为例，state当等于0时，表示当前同步队列的锁还没有被获取，属于可争夺的状态。

###### 	2、通过CAS将state改为+1，成功后即可控制该队列（队列的控制权由AQS中的一个owner字段来登记，谁将state修改成功，谁就能修改owner，state加成功：owner=自身线程；state=0：owner=null表示当前队列无线程控制，准许竞争）。

###### 	3、这时的队列只进（进的是state修改失败的线程，需要等待state变为0的入队排队）不出，出的权利由owner控制。

###### 	4、具体是在owner线程执行完任务后控制该队列的头部第二个节点的线程唤醒，唤醒通过LockSupport.unpark，唤醒后的线程会再次从步骤1循环执行（抢锁-->成功-->修改owner-->运行业务--->修改state减操作至0--->owner=null--->释放队列第二个节点线程循环，抢锁失败则继续park在队列）。

###### 		.至于唤醒的为什么会是第二个节点，这是由于设计者在设计时考虑到方便对链表判空，为空时需要新建头结点在高并发场景下不是原子性操作，头结点的创建很容易出现问题（我自己尝试写过简易版AQS，没有设置哨兵节点，头结点那里出了太多问题，不是最后头结点不出队park在那里就是第一个创建完头结点以后又往后创建了一个同样节点插入到后面，再就是release还容易出现空指针，既不好发现也不容易修改），所以直接创建一个哨兵节点，线程设为null，简化操作，后续线程不需要判空直接入队，release时也不需要判空。

###### 		设置哨兵节点的第二个目的，更重要的是起到唤醒后方线程的作用。由于实际情况下线程执行任务过程中会出现几种状态（Runnable、waiting、等），所以在线程可中断或取消任务时需要离队，哨兵节点就是通过自己节点中的一个status字段来判断后驱节点是不是等待状态，是的话唤醒，不是的话说明后方线程取消了任务，就会跳过它。如果没有这个status来给后驱线程打标签，当前方线程唤醒的后驱线程已经离队，LockSupport.unpark(null)，那后面所有沉睡的线程都阻塞在那里，而且也没法唤醒，内存泄漏了，任务大批量中断，问题相当严重。



#### Condition：

​	Condition是ReentrentLock下的一个子类，维护一个单向链表构成的队列，用来存放满足特定条件的线程，并让其进入park状态（通过使用ForkJoin中的managedBlock方法，实现ForkJoinPool.ManagedBlocker接口，重写释放的条件，满足条件，这里是中断或者取消任务，则释放该线程，不满足则park在这里）。

##### await（）：

###### 	1、当调用Condition.await()，会先将该线程放到condition的单向链表中。

###### 	2、完成后释放AQS的锁，将state保存，清空设置state=0，同时唤醒AQS的第二个节点线程。

###### 	3、使用ForkJoin的managedBlock来管理线程状态，通过重写接口中方法，满足条件时释放，不满足条件park，达到阻塞线程的目的。

```java
public final void await() throws InterruptedException {
    if (Thread.interrupted())
        throw new InterruptedException();
    ConditionNode node = new ConditionNode();
    //这里将新建节点加入Condition的等待队列，保存state状态，释放锁，设置owner=null，唤醒AQS头部线程
    int savedState = enableWait(node);
    LockSupport.setCurrentBlocker(this); // for back-compatibility
    boolean interrupted = false, cancelled = false, rejected = false;
    //这里是确认该线程是否还在AQS里，因为线程在获取锁之后首先把自己节点的thread清空，所以正常情况下执行业务的线程都已不在
    //AQS队列，这里是确保线程已经出AQS队列，才能继续在条件等待队列中挂起
    while (!canReacquire(node)) {
        if (interrupted |= Thread.interrupted()) {
            if (cancelled = (node.getAndUnsetStatus(COND) & COND) != 0)
                break;              // else interrupted after signal
            //这里是判断条件，当节点status是cond状态，即满足条件时，执行以下操作
        } else if ((node.status & COND) != 0) {
            try {
                if (rejected)
                    node.block();
                else
                    //将线程挂起，这里用的forkJoin线程池的管理线程方法，将ConditionNode实现managedBlocker接口，重写释放与阻塞条件
                    //满足条件则让其自旋，不满足则释放线程，这里Condition重写了阻塞方法，即将线程park，只有当被唤醒，同时status状态从cond设置成
                    //waiting或者取消时才会取消挂起，继续执行。
                    //这里在signal()时不会立刻被唤醒，signal只是将这个线程从条件队列放到了AQS阻塞队列中，并修改了status值为0
                    //具体唤醒的操作是owner的线程在释放锁之后unpark，这时才会被唤醒，重新在这里往下进行。
                    ForkJoinPool.managedBlock(node);
            } catch (RejectedExecutionException ex) {
                rejected = true;
            } catch (InterruptedException ie) {
                interrupted = true;
            }
        } else
            Thread.onSpinWait();    // awoke while enqueuing
    }
    LockSupport.setCurrentBlocker(null);
    node.clearStatus();
    //这里是线程唤醒以后再次尝试获取锁（CAS操作AQS），获取后继续执行业务，失败继续park等待owner执行unpark
    acquire(node, savedState, false, false, false, 0L);
    if (interrupted) {
        if (cancelled) {
            unlinkCancelledWaiters(node);
            throw new InterruptedException();
        }
        Thread.currentThread().interrupt();
    }
}
```

###### 	4、在其他线程调用signal()，将从条件队列脱离，加入AQS同步队列等待owner唤醒。



#### signal():

##### 	将条件等待队列中的头部节点出队，并加入AQS队列尾部。

###### 	1、Condition.signal()，首先获取该等待队列中的头结点，判断status是COND的，将头结点从该队列去除，并将它放到AQS的队尾（自旋执行，直到入队尾成功），入队后判断前驱线程的status是否为取消状态，是的话unpark释放该线程，不是则任务完成，继续执行相关业务。

```java
public final void signal() {
    //拿取条件队列的头结点
    ConditionNode first = firstWaiter;
    if (!isHeldExclusively())
        throw new IllegalMonitorStateException();
    if (first != null)
        //开始入队操作
        doSignal(first, false);
}
```

​	下面是入队操作：

```java
private void doSignal(ConditionNode first, boolean all) {
    while (first != null) {
        ConditionNode next = first.nextWaiter;
        //先让头结点出队
        if ((firstWaiter = next) == null)
            lastWaiter = null;
        //判断节点status是COND状态的进行入AQS队列
        if ((first.getAndUnsetStatus(COND) & COND) != 0) {
            //开始入队操作
            enqueue(first);
            //不是signalAll的话，直接退出，否则继续，直到清空条件队列
            if (!all)
                break;
        }
        first = next;
    }
}
```

开始入队AQS：

```java
final void enqueue(Node node) {
    if (node != null) {
        for (;;) {
            Node t = tail;
            //设置前驱节点为AQS的入队前的尾结点
            node.setPrevRelaxed(t);        // avoid unnecessary fence
            if (t == null)                 // initialize
                tryInitializeHead();
            //CAS入队，不成功则自旋，直到入队成功
            else if (casTail(t, node)) {
                //成功后将原尾结点指针指向自身节点，入队成功
                t.next = node;
                if (t.status < 0)          // wake up to clean link
                    //查看尾结点是否为取消状态，是的话会唤醒新加入的thread
                    LockSupport.unpark(node.waiter);
                break;
            }
        }
    }
}
```

##### 入队后，该线程继续维持park状态，阻塞在forkJoin的managedBlocker中，等待owner释放锁并且unpark后才被唤醒。



> [!IMPORTANT]
>
> 注意：
>
> ###### signal仅仅是将等待队列的头结点取出放到了AQS同步队列尾部，并修改了它的status=0，并没有唤醒该线程。
>
> ###### 做了这些之后该节点的线程仍然保持挂起状态（除非前驱节点已经是取消状态会立刻唤醒），只有等待owner（AQS持有锁的线程）执行完成后主动release，释放锁，unpark唤醒AQS中第一个线程后才会被唤醒。所以它必须成为AQS队列第二节点才会被唤醒！！！没被唤醒时仍然卡在await方法的managedBlocker()中。
>
> ###### 唤醒以后的线程从managedBlocker的条件判断循环中走出来，先查看AQS队列中有没有自己，有的话再获取AQS的锁，获取到锁以后成为owner才会从await方法中跳出，继续执行后续代码。如果获取不到锁，则会在AQS的队列中继续park，等待被owner唤醒，依次循环。

