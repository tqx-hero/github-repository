package com.tqx.thread.lock;

import java.util.concurrent.locks.ReentrantLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/16 18:31
 */
public class Fair {

    private static ReentrantLock lock = new ReentrantLock();

    static class woker extends Thread {
        public woker(String name) {
            super(name);
        }

        @Override
        public void run() {
            for (int i = 1; i <= 3; i++) {
                try {
                    lock.lock();
                    System.out.println("线程：" + Thread.currentThread().getName() + "获取到了锁");
                } catch (Exception e) {
                } finally {
                    if (lock.isHeldByCurrentThread()) {
                        lock.unlock();
                    }
                }

            }
        }
    }

    public static void main(String[] args) {
        woker a = new woker("A");
        woker b = new woker("B");
        woker c = new woker("C");
        a.start();
        b.start();
        c.start();
    }

}
