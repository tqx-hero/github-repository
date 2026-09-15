package com.tqx.thread.lock;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/16 18:54
 */
public class ReadWriteLock {

    private static ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

    private static ReentrantReadWriteLock.ReadLock readLock = lock.readLock();
    private static ReentrantReadWriteLock.WriteLock writeLock = lock.writeLock();


    static void read() {
        try {
            readLock.lock();
            System.out.println(Thread.currentThread().getName() + "进入了读锁");
            TimeUnit.SECONDS.sleep(3);
        } catch (Exception e) {
        } finally {
            readLock.unlock();
        }
    }

    static void write() {

        try {
            writeLock.lock();
            System.out.println(Thread.currentThread().getName() + "进入了写锁");
            TimeUnit.SECONDS.sleep(3);
        } catch (Exception e) {
        } finally {
            writeLock.unlock();
        }

    }

    public static void main(String[] args) {
        Thread t1 = new Thread(() -> {
            read();
        });
        Thread t2 = new Thread(() -> {
            read();
        });
        Thread t3 = new Thread(() -> {
            write();
        });
        Thread t4 = new Thread(() -> {
            write();
        });
        t1.start();
        t3.start();
        t4.start();
        t2.start();
    }

}
