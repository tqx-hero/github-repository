package com.tqx.test;

import java.util.concurrent.Semaphore;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/6/7 22:35
 */
public class JiaoTiPrint2 {

    private static final Semaphore s1 = new Semaphore(1);
    private static final Semaphore s2 = new Semaphore(0);
    private static final Semaphore s3 = new Semaphore(0);

    private static class Thread1 extends Thread {
        @Override
        public void run() {
            try {
                s1.acquire();
                System.out.println("线程1: A");
                s2.release();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }

    private static class Thread2 extends Thread {
        @Override
        public void run() {
            try {
                s2.acquire();
                System.out.println("线程2: B");
                s3.release();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }

    private static class Thread3 extends Thread {
        @Override
        public void run() {
            try {
                s3.acquire();
                System.out.println("线程3: C");
                s1.release();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }

    public static void main(String[] args) {
        for (int i = 0; i < 20; i++) {
            new Thread1().start();
            new Thread2().start();
            new Thread3().start();
        }
    }
}
