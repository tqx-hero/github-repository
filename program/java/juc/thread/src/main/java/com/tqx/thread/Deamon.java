package com.tqx.thread;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/14 22:09
 */
public class Deamon {

    public static void main(String[] args) {
        Thread t1 = new Thread(() -> {
            for (int i = 0; i < 100; i++) {
                System.out.println(i);
            }
        });

        t1.setDaemon(true);
        t1.start();
        System.out.println("主线程结束");
    }
}
