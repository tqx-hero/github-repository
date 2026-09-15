package com.tqx.thread.park;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/18 8:38
 */
public class Unpark {

    public static void main(String[] args) {

        Thread t2 = new Thread(() -> {
            try {
                TimeUnit.SECONDS.sleep(1);
                LockSupport.park();
                System.out.println("B");

            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

        }, "thread2");
        t2.start();

        Thread t3 = new Thread(() -> {
            try {
                TimeUnit.SECONDS.sleep(2);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            LockSupport.park();
            System.out.println("C");
            LockSupport.unpark(t2);
        }, "thread3");


        new Thread(() -> {
//                TimeUnit.SECONDS.sleep(2);
                System.out.println("A");
                LockSupport.unpark(t3);
        }).start();

        t3.start();
    }
}
