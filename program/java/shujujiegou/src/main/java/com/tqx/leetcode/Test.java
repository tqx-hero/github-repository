package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/1 16:43
 */
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Semaphore;

public class Test {

    static class H2O {
        private CountDownLatch CDL = new CountDownLatch(3);
        private final Semaphore S_H = new Semaphore(2);
        private final Semaphore S_O = new Semaphore(1);
        private String water;
        private char[] waterArr;
        public H2O() {}

        public void hydrogen(Runnable releaseHydrogen) throws InterruptedException {
            S_H.acquire();

            // 1. 先倒数
            CDL.countDown();

            // 2. 等待凑齐 3 个
            CDL.await();

            // 3. 输出
            releaseHydrogen.run();

            S_H.release();
        }

        public void oxygen(Runnable releaseOxygen) throws InterruptedException {
            S_O.acquire();

            CDL.countDown(); // 这个一定是最后一个倒数的！
            CDL.await();

            releaseOxygen.run();

            // ====================== 关键修复：在这里重置！======================
            // O 是最后一个到达的，它负责创建下一轮的 latch
            CDL = new CountDownLatch(3);

            S_O.release();
        }

        public H2O(String water) {
            this.water = water;
            this.waterArr = water.toCharArray();
        }

        // 启动线程
        public void createWater(String s) {
            for (char c : s.toCharArray()) {
                if (c == 'H') {
                    new Thread(() -> {
                        try {
                            hydrogen(() -> System.out.print("H"));
                        } catch (InterruptedException e) {}
                    }).start();
                } else {
                    new Thread(() -> {
                        try {
                            oxygen(() -> System.out.print("O"));
                        } catch (InterruptedException e) {}
                    }).start();
                }
            }
        }


    }

    public static void main(String[] args) {
        H2O h2O = new H2O("OOHHHH");
        h2O.createWater("OOHHHH");
    }
}