package com.tqx.thread.juc;

import java.util.concurrent.Semaphore;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/18 22:21
 */
public class SemaphoreDemo {

    private static Semaphore semaphore = new Semaphore(3);

    public static void main(String[] args) {

//        for (int i = 0; i < 10; i++) {
        final int nums = 20;
        new Thread(() -> {
            try {
                semaphore.acquire(10);
                System.out.println("num =" + nums);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }).start();
//        }

        for (int i = 10; i < 17; i++) {
            final int num = i;
            new Thread(() -> {
                System.out.println("num =" + num);
                semaphore.release();
            }).start();
        }
    }
}
