package com.example.test.sync;

import lombok.extern.slf4j.Slf4j;

/**
 * @author Administrator
 * @version 1.0
 * @description: synchronized用法 :锁当前实例(this)，不同实例之间不会影响
 * 输出结果：
 * 线程2 -> count=1
 * 线程1 -> count=1
 * 线程2 -> count=2
 * 线程1 -> count=2
 * 线程2 -> count=3
 * 线程1 -> count=3
 * 线程2 -> count=4
 * 线程1 -> count=4
 * 线程2 -> count=5
 * 线程1 -> count=5
 * @date 2026/2/24 6:30
 */
public class SyncTest {

    private int count = 0;

    synchronized void add() {
        count++;
        System.out.println(Thread.currentThread().getName() + " -> count=" + count);
    }

    public static void main(String[] args) {
        SyncTest syncTest = new SyncTest();

        //两个不同实例启动线程不会相互受到影响
        SyncTest syncTest1 = new SyncTest();
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
