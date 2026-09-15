package com.tqx.thread;

import java.util.concurrent.TimeUnit;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/14 21:21
 */
public class interupter {

    public static void main(String[] args) {
        Thread thread = new Thread(() -> {
            for (int i = 0; i < 10; i++) {
                System.out.println(Thread.currentThread().getName() + ": " + i);
            }
            while (true) {
                try {
                    TimeUnit.SECONDS.sleep(10);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    Thread.currentThread().interrupt();
                }

                System.out.println("线程是否被打断：" + Thread.currentThread().isInterrupted());
                if (Thread.interrupted()) {
                    System.out.println("线程是否被打断：" + Thread.currentThread().isInterrupted());
                    break;
                }
            }
        });
        thread.start();
        thread.interrupt();
        System.out.println("主线程");
    }
}
