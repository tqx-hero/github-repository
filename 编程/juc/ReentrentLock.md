## ReentrentLock

可重入锁，比synchroinzed更灵活，锁的粒度更细，但注意锁的释放，必须放到finally中

```java
public class Reetrent {

    public static Integer num = 10000;

    private static ReentrantLock lock = new ReentrantLock();

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < 10000; i++) {
            Thread t1 = new Thread(() ->
                    des()
            );
            t1.start();
        }
        TimeUnit.SECONDS.sleep(5);
        System.out.println("库存=" + num);

    }
    public static void des() {
        try {
            lock.lock();
            num--;
        } catch (Exception e) {
        } finally {
            if (lock.isHeldByCurrentThread()) {
                lock.unlock();
            }
        }
    }
}
```

### tryLock：

有两个重载方法，尝试获取锁，如果获取到返回true，没获取到返回false

tryLock():只尝试一次，获取到和没获取到都直接返回。

```java
public static void getLock() throws InterruptedException {
     System.out.println("线程 : " + Thread.currentThread().getName() + " ,尝试获取锁");
     try {Thread.sleep(2000);
         if (lock.tryLock()) {
             System.out.println("线程 : " + Thread.currentThread().getName() + " ,获取到了锁");
         } else {
             System.out.println("线程 : " + Thread.currentThread().getName() + " ,未获取到锁");
             Thread.sleep(1000);
         }
     } catch (Exception e) {
     } finally {
         if (lock.isHeldByCurrentThread()) {
             lock.unlock();
         }
     }
 }
```



tryLock(long timeout, TimeUnit unit)：与上面不同时在一定时间内尝试获取，规定时间内获取到返回true，没获取到或时间结束返回false

```
public static void getLock() throws InterruptedException {
     System.out.println("线程 : " + Thread.currentThread().getName() + " ,尝试获取锁");
     try {Thread.sleep(2000);
     //添加时间限制，在时间内获取返回true
         if (lock.tryLock(2, TimeUnit.SECONDS)) {
             System.out.println("线程 : " + Thread.currentThread().getName() + " ,获取到了锁");
         } else {
             System.out.println("线程 : " + Thread.currentThread().getName() + " ,未获取到锁");
             Thread.sleep(1000);
         }
     } catch (Exception e) {
     } finally {
         if (lock.isHeldByCurrentThread()) {
             lock.unlock();
         }
     }
 }
```

#### lockInterruptibly：

尝试获取锁，并可以通过thread.interrupt()方法来中断（给线程打上中断标记，lockInterruptibly()内部又调用了静态方法判断标记），与Condition配合可以进行灵活的处理一些根据条件来执行业务的功能。

```java
class LockInterrupt {
    private static ReentrantLock lock = new ReentrantLock();

    public static void main(String[] args) throws InterruptedException {
        new Thread(() -> interrupt(), "A").start();
        TimeUnit.MILLISECONDS.sleep(200);
        Thread thread = new Thread(() -> interrupt(), "B");
        thread.start();
        TimeUnit.SECONDS.sleep(2);
        //调用interrupt方法后，可以打断通过lockInterruptibly()尝试获取锁的阻塞线程
        thread.interrupt();
    }

    public static void interrupt() {
        try {
            lock.lockInterruptibly();
            System.out.println("线程：" + Thread.currentThread().getName() + "获取到了锁");
            TimeUnit.SECONDS.sleep(5);
        } catch (InterruptedException e) {
            System.out.println("出现异常：");
        } finally {
            if (lock.isHeldByCurrentThread()) {
                lock.unlock();
            }
        }
    }
}
```

源码如下：

```java
    public final void acquireInterruptibly(int arg)
        throws InterruptedException {
        if (Thread.interrupted() ||
            (!tryAcquire(arg) && acquire(null, arg, false, true, false, 0L) < 0))
            throw new InterruptedException();
    }
```

这里调用了静态方法：Thread.interrupted()，该方法会判断是否存在中断标记，同时在返回结果时清除中断标记。

#### 公平锁与非公平锁：

公平锁讲究的是队列中的线程先来后到，遵循FIFO原则。

非公平锁当线程执行完成任务后会再次尝试获取锁，获取到则继续执行任务，没获取到则去队列排队。

非公平锁由于允许线程进行非公平抢锁，这一定程度上省去了CPU切换上下文的开销，提高CPU的利用率，对吞吐量有了一定提升。但是对于长时间获取不到锁的线程来说会导致饥饿。除非对排序有非常严格的要求，还是以非公平锁为先。

### 与synchroinzed的对比：

​	1、synchroinzed是底层C++实现的，有锁升级降级过程，ReentrentLock是java实现的。

​	2、synchroinzed可重入、不可中断、非公平；ReentrentLock可重入、可中断（通过tryLock()或者lockInterruptibly()实现定时中断或调用interrupt()中断），公平与非公平均可。

​	3、synchroinzed锁粒度更粗，无法自由控制锁的释放；ReentrentLock可以自由控制锁的加减，自由度更高。

​	4、synchroinzed适合锁少量的代码块，这样不容易升级成重锁的话效率非常高，ReentrentLock适合锁大量的代码块。