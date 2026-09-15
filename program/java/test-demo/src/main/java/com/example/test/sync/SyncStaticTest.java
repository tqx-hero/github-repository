package com.example.test.sync;

/**
 * @author Administrator
 * @version 1.0
 * @description: synchronized用法 (static),锁静态代码块，创建两个实例开启线程后会互相影响输出结果
 * 输出结果：
 * 线程1 -> count=1
 * 线程1 -> count=2
 * 线程1 -> count=3
 * 线程1 -> count=4
 * 线程1 -> count=5
 * 线程2 -> count=6
 * 线程2 -> count=7
 * 线程2 -> count=8
 * 线程2 -> count=9
 * 线程2 -> count=10
 * @date 2026/2/24 6:30
 */
public class SyncStaticTest {

    private static int count = 0;

    static synchronized void add() {
        count++;
        System.out.println(Thread.currentThread().getName() + " -> count=" + count);
    }

    public static void main(String[] args) {
        SyncStaticTest syncTest = new SyncStaticTest();
        SyncStaticTest syncTest1 = new SyncStaticTest();
        new Thread(() -> {
            for (int i = 0; i < 5; i++) {
                syncTest.add();
            }
        }, "线程1").start();

        new Thread(() -> {
            for (int i = 0; i < 5; i++) {
                syncTest1.add();
            }
        }, "线程2").start();
    }

}
