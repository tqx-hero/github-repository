package com.tqx.thread;

import java.util.concurrent.TimeUnit;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/14 21:52
 */
public class Join {

    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(() -> {

            try {
                TimeUnit.SECONDS.sleep(5);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

            System.out.println("子线程执行完毕");
        });

        thread.start();
        thread.join();
        System.out.println("主线程执行完毕");
    }
}
