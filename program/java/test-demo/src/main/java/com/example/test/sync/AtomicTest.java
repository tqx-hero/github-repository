package com.example.test.sync;

import java.util.concurrent.atomic.AtomicInteger;

/**
 * @author Administrator
 * @version 1.0
 * @description: AtomicInteger 原子类进行计数，但是会有ABA问题
 * @date 2026/2/24 8:39
 */

public class AtomicTest {
    private static final AtomicInteger count = new AtomicInteger(0);

    void add() {
        int increment = count.incrementAndGet();
        System.out.println(Thread.currentThread().getName() + " count= " + increment);
    }

    public static void main(String[] args) {
        AtomicTest atomicTest = new AtomicTest();
        new Thread(() -> {
            for (int i = 0; i < 5; i++)
                atomicTest.add();
        }, "线程1").start();

        new Thread(() -> {
            for (int i = 0; i < 5; i++)
                atomicTest.add();
        }, "线程2").start();
    }

}
