package com.example.test.sync;

/**
 * @author Administrator
 * @version 1.0
 * @description: synchronized用法 :锁指定对象(final定义的对象)，而不是锁代码块，运行效率更高，也能灵活的指定锁对象，多个实例的线程不受影响
 * 输出结果：
 * 线程1 -> count=1
 * 线程2 -> count=1
 * 线程1 :执行非同步逻辑
 * 线程2 :执行非同步逻辑
 * 线程1 -> count=2
 * 线程2 -> count=2
 * 线程1 :执行非同步逻辑
 * 线程2 :执行非同步逻辑
 * 线程1 -> count=3
 * 线程1 :执行非同步逻辑
 * 线程1 -> count=4
 * 线程1 :执行非同步逻辑
 * 线程1 -> count=5
 * 线程1 :执行非同步逻辑
 * 线程2 -> count=3
 * 线程2 :执行非同步逻辑
 * 线程2 -> count=4
 * 线程2 :执行非同步逻辑
 * 线程2 -> count=5
 * 线程2 :执行非同步逻辑
 * @date 2026/2/24 6:30
 */
public class SyncFinalTest {

    private int count = 0;
    //自定义锁对象，用final修饰防止锁对象被修改
    private final Object lock = new Object();

    void add() {
        synchronized (lock) {
            count++;
            System.out.println(Thread.currentThread().getName() + " -> count=" + count);
        }
        System.out.println(Thread.currentThread().getName() + " :执行非同步逻辑");
    }

    public static void main(String[] args) {
        SyncFinalTest syncTest = new SyncFinalTest();

        //两个不同实例启动线程不会相互受到影响
        SyncFinalTest syncTest1 = new SyncFinalTest();
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
