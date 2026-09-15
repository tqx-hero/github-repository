package com.example.test.sync;

/**
 * @author Administrator
 * @version 1.0
 * @description: synchronized用法 :锁指定对象(final static定义的对象)，锁定该常量，多线程之间会受影响
 * 输出结果：
 * 线程1 -> count=1
 * 线程2 -> count=2
 * 线程2 :执行非同步逻辑
 * 线程1 :执行非同步逻辑
 * 线程2 -> count=3
 * 线程2 :执行非同步逻辑
 * 线程1 -> count=4
 * 线程1 :执行非同步逻辑
 * 线程2 -> count=5
 * 线程2 :执行非同步逻辑
 * 线程2 -> count=6
 * 线程2 :执行非同步逻辑
 * 线程2 -> count=7
 * 线程2 :执行非同步逻辑
 * 线程1 -> count=8
 * 线程1 :执行非同步逻辑
 * 线程1 -> count=9
 * 线程1 :执行非同步逻辑
 * 线程1 -> count=10
 * 线程1 :执行非同步逻辑
 * @date 2026/2/24 6:30
 */
public class SyncStaticFinalTest {

    private static int count = 0;
    //自定义锁对象，这里用final static 定义的常量
    private final static Object lock = new Object();

    void add() {
        synchronized (lock) {
            count++;
            System.out.println(Thread.currentThread().getName() + " -> count=" + count);
        }
        System.out.println(Thread.currentThread().getName() + " :执行非同步逻辑");
    }

    public static void main(String[] args) {
        SyncStaticFinalTest syncTest = new SyncStaticFinalTest();

        //两个不同实例启动线程不会相互受到影响
        SyncStaticFinalTest syncTest1 = new SyncStaticFinalTest();
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
