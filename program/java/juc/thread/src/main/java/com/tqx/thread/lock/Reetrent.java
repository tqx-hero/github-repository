package com.tqx.thread.lock;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/16 16:25
 */
public class Reetrent {

    public static Integer num = 10000;

    private static ReentrantLock lock = new ReentrantLock();

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < 4; i++) {
            Thread t1 = new Thread(() ->
                    des()
            );
            t1.start();
        }
        TimeUnit.SECONDS.sleep(1);
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

class TryLockT {

    private static ReentrantLock lock = new ReentrantLock();

    public static void main(String[] args) {
        new Thread(() -> {
            try {
                getLock();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }, "A").start();
        new Thread(() -> {
            try {
                getLock();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }, "B").start();

    }

    public static void getLock() throws InterruptedException {
        System.out.println("线程 : " + Thread.currentThread().getName() + " ,尝试获取锁");
        try {
            Thread.sleep(2000);
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
}

class LockInterrupt {
    private static ReentrantLock lock = new ReentrantLock();

    public static void main(String[] args) throws InterruptedException {
        new Thread(() -> interrupt(), "A").start();
        TimeUnit.MILLISECONDS.sleep(200);
        Thread thread = new Thread(() -> interrupt(), "B");
        thread.start();
        TimeUnit.SECONDS.sleep(2);
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
