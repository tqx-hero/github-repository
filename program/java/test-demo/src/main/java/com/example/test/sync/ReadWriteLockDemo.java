package com.example.test.sync;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: 读写锁ReentrantReadWriteLock 用法 ：
 * 1、读锁共享，写锁排他，所以非常适合读取操作多的场景，其他场景可使用synchronized、ReentrantLock等锁
 * 2、多线程进行读取操作时可共享读锁同时进行，只要没有线程持有写锁
 * 3、但写锁不能线程之间共享，多个写线程会串行执行
 * 4、写-读互斥，即一个线程只要持有写锁，其他线程不能获取任何锁（包括读锁和写锁
 * 5、只要有一个线程持有读锁，所有线程均不能获取写锁，所以读锁不能主动升级，如果需要，可用tryLock()方法进行升级写锁
 * 6、写锁可降级，如一个线程如持有写锁，在释放写锁之前这个线程可再次获取读锁，在写锁被释放以后可继续持有读锁
 * 7、读锁和写锁都是可重入锁，即一个线程获取读锁（写锁）后可以多次获取读锁（写锁）而不发生死锁
 * @date 2026/2/24 10:11
 */
public class ReadWriteLockDemo {

    //缓存容器，非线程安全
    private final Map<String, Object> cache = new HashMap<>();
    //定义读写锁核心对象
    private final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();
    //定义读锁（共享锁）
    private final ReentrantReadWriteLock.ReadLock readLock = lock.readLock();
    //定义写锁（排它锁）
    private final ReentrantReadWriteLock.WriteLock writeLock = lock.writeLock();


    Object read(String key) {
        readLock.lock();
        try {
            //模拟读操作
//            Thread.sleep(100);
            return cache.get(key);
        } catch (Exception e) {
            Thread.currentThread().interrupt();
            return null;
        } finally {
            readLock.unlock();
            System.out.println(Thread.currentThread().getName() + " 释放读锁");
        }
    }

    void write(String key, Object value) {
        writeLock.lock();
        try {
            //模拟写操作
//            Thread.sleep(200);
            cache.put(key, value);
        } catch (Exception e) {
            Thread.currentThread().interrupt();
        } finally {
            writeLock.unlock();
            System.out.println(Thread.currentThread().getName() + " 释放写锁");
        }
    }

    void delete(String key) {
        writeLock.lock();
        try {
            System.out.println(Thread.currentThread().getName() + "删除缓存");
            cache.remove(key);
        } catch (Exception e) {
            Thread.currentThread().interrupt();
        } finally {
            writeLock.unlock();
            System.out.println(Thread.currentThread().getName() + " 释放写锁(删除)");
        }
    }

    public static void main(String[] args) {
//        ReentrantLock
        ReadWriteLockDemo cache = new ReadWriteLockDemo();
        for (int i = 0; i < 10; i++) {
            int finalI = i;
            new Thread(() ->
                    cache.read("key_" + finalI)
                    , "读线程_" + finalI).start();
        }

        for (int i = 0; i < 10; i++) {
            int finalIs = i;
            new Thread(() ->
                    cache.write("key_" + finalIs, "value_" + finalIs)
                    , "写线程_" + finalIs).start();
        }
    }

}
