package com.spring.sync;

import org.openjdk.jol.info.ClassLayout;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/16 15:02
 */
public class Test {

    public static void main(String[] args) throws InterruptedException {
        Object lock = new Object();
        System.out.println(ClassLayout.parseInstance(lock).toPrintable());
        // 多线程竞争触发锁膨胀为重量级锁
        new Thread(() -> {
            synchronized (lock) {
            }
        }).start();
        Thread.sleep(100); // 等待锁膨胀

        synchronized (lock) {
            System.out.println("重量级锁（Monitor）的对象头：");
            System.out.println(ClassLayout.parseInstance(lock).toPrintable());
        }
    }
}


