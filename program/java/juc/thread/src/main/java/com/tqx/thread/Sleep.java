package com.tqx.thread;

import java.util.concurrent.TimeUnit;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/14 20:58
 */
public class Sleep {

    public static void main(String[] args) {

        Thread thread1 = new Thread(() -> {
            System.out.println("线程1启动");
            Thread.yield();
            for (int i = 0; i < 100; i++) {
                System.out.println(Thread.currentThread().getName() + ":" + i);
            }
        }, "线程1");
        Thread thread2 = new Thread(() -> {
            for (int i = 0; i < 100; i++) {
                System.out.println(Thread.currentThread().getName() + ":" + i);
            }
        }, "线程2");

        thread1.start();
        thread2.start();
    }
}
