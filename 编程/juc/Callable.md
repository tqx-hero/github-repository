## Callable

实现callable接口方式，用来创建一个能返回方法执行完后返回值的一个线程。

由于Callable接口与Runnable非继承关系，且Thread只能传入Runnable接口的实例，所以必须使用中介FutureTask。

FutureTask构造方法可以实现将Callable接口注入：

```java
public FutureTask(Callable<V> callable) {
    if (callable == null)
        throw new NullPointerException();
    this.callable = callable;
    this.state = NEW;       // ensure visibility of callable
}
```

同时FutureTask实现了Runnable接口的子类接口RunnableFuture：

```java
public class FutureTask<V> implements RunnableFuture<V> 
```

```java
public interface RunnableFuture<V> extends Runnable, Future<V>
```

所以可以通过：

```java
new Thread(futureTask)
```

方式将Callable与Thread联系起来，创建线程并执行：

```java
public static void main(String[] args) {
    //创建FutureTask实例，注入Callable接口
    FutureTask<Integer> futureTask = new FutureTask<>(() -> {
        int s = 0;
        for (int i = 0; i < 100; i++) {
            s += i;
        }
        return s;
    });

    Thread thread = new Thread(futureTask);
    thread.start();
    try {
        //调用futureTask.get()方法可获取子线程的运行结果，包括异常
        System.out.println("返回值==" + futureTask.get());
    } catch (Exception e) {
        throw new RuntimeException(e);
    }
    System.out.println("主线程执行结束");
}
```

futureTask.get()方法可以获取返回结果或异常信息。该方法的特殊之处在于不需要额外的join操作，它自己会等待子线程执行结束后才会返回。

底层是运用了一个以线程为value创建的单向链表，作用是将等待任务执行的线程放入链表中。并判断任务有没有执行完成，没有执行完则进入阻塞状态LockSupport.park()，执行完成则释放链表中的等待线程，同时返回结果。

源码如下：

```java
public V get() throws InterruptedException, ExecutionException {
    int s = state;
    //任务刚开始时state=0，任务未执行完时则会进入awaitDone方法
    if (s <= COMPLETING)
        s = awaitDone(false, 0L);
    return report(s);
}
```

awaitDone()方法源码如下：

```java
private int awaitDone(boolean timed, long nanos)
    throws InterruptedException {
    // The code below is very delicate, to achieve these goals:
    // - call nanoTime exactly once for each call to park
    // - if nanos <= 0L, return promptly without allocation or nanoTime
    // - if nanos == Long.MIN_VALUE, don't underflow
    // - if nanos == Long.MAX_VALUE, and nanoTime is non-monotonic
    //   and we suffer a spurious wakeup, we will do no worse than
    //   to park-spin for a while
    long startTime = 0L;    // Special value 0L means not yet parked
    WaitNode q = null;
    boolean queued = false;
    for (;;) {
        int s = state;
        //任务执行完成后，进入该if代码块内，清空等待链表，并返回结果
        if (s > COMPLETING) {
            if (q != null)
                q.thread = null;
            return s;
        }
        else if (s == COMPLETING)
            // We may have already promised (via isDone) that we are done
            // so never return empty-handed or throw InterruptedException
            Thread.yield();
        else if (Thread.interrupted()) {
            //如果线程被打断，移出所有等待链表，并抛出异常。
            removeWaiter(q);
            throw new InterruptedException();
        }
        else if (q == null) {
            //第一次进来尝试获取值，会new WaitNode()，该构造方法会将当前线程，也就是主线程放入链表中。
            if (timed && nanos <= 0L)
                return s;
            q = new WaitNode();
        }
        else if (!queued)
        
            queued = WAITERS.weakCompareAndSet(this, q.next = waiters, q);
        else if (timed) {
            final long parkNanos;
            if (startTime == 0L) { // first time
                startTime = System.nanoTime();
                if (startTime == 0L)
                    startTime = 1L;
                parkNanos = nanos;
            } else {
                long elapsed = System.nanoTime() - startTime;
                if (elapsed >= nanos) {
                    removeWaiter(q);
                    return state;
                }
                parkNanos = nanos - elapsed;
            }
            // nanoTime may be slow; recheck before parking
            if (state < COMPLETING)
                LockSupport.parkNanos(this, parkNanos);
        }
        //这里是当子线程未执行完成的操作，直接阻塞，等待执行完成后唤醒。
        else
            LockSupport.park(this);
    }
}
```

所以主线程会一直等待子线程执行完成，拿到结果后继续执行。





### 创建线程的几种方式

​	1、继承Thread类，重写run方法

​	2、实现runnable接口，重写run方法

​	3、实现Callable接口，并创建FutureTask实例，new Thread（new FutureTask(Callable)）方式。