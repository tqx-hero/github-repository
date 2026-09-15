package com.example.test.sync;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/24 12:32
 */
public class ReetrantReadToWrite {

    private final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();
    private final ReentrantReadWriteLock.ReadLock readLock = lock.readLock();
    private final ReentrantReadWriteLock.WriteLock writeLock = lock.writeLock();

    private static List<Object> map1;

    static {
        map1 = List.of("1", "str1"
                , "2", "str2", "3", "str3");
    }

    void readAndWrite(int i, Object value) {
        readLock.lock();
        try {
            System.out.println("原集合内数据=" + map1.toString());

            if (writeLock.tryLock()) {
                try {
                    if (i > map1.size())
                        map1.add(value);
                    else
                        map1.add(i, value);
                    System.out.println("现集合内数据=" + map1);
                } finally {
                    writeLock.unlock();
                }
            }

        } finally {
            readLock.unlock();
        }

    }

    public static void main(String[] args) {
        new Thread(() -> {
            ReetrantReadToWrite readToWrite = new ReetrantReadToWrite();
            for (int i = 1; i <= 2; i++) {
                readToWrite.readAndWrite(i, map1.get(i) + Thread.currentThread().getName());
            }
        }, "线程1").start();
        new Thread(() -> {
            ReetrantReadToWrite readToWrite = new ReetrantReadToWrite();
            for (int i = 1; i <= 2; i++) {
                readToWrite.readAndWrite(i, map1.get(i) + Thread.currentThread().getName());
            }
        }, "线程2").start();
    }

}
