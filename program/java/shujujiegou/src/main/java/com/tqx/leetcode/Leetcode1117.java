package com.tqx.leetcode;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: 生成水
 * 现在有两种线程，氧 oxygen 和氢 hydrogen，你的目标是组织这两种线程来产生水分子。
 * 存在一个屏障（barrier）使得每个线程必须等候直到一个完整水分子能够被产生出来。
 * 氢和氧线程会被分别给予 releaseHydrogen 和 releaseOxygen 方法来允许它们突破屏障。
 * 这些线程应该三三成组突破屏障并能立即组合产生一个水分子。
 * 你必须保证产生一个水分子所需线程的结合必须发生在下一个水分子产生之前。
 * 换句话说:
 * • 如果一个氧线程到达屏障时没有氢线程到达，它必须等候直到两个氢线程到达。
 * • 如果一个氢线程到达屏障时没有其它线程到达，它必须等候直到一个氧线程和另一个氢线程到达。
 * 书写满足这些限制条件的氢、氧线程同步代码。 
 * 示例 1:
 * 输入:
 * water = "HOH"
 * 输出:
 * "HHO"
 * 解释:
 * "HOH" 和 "OHH" 依然都是有效解。
 * 示例 2:
 * 输入:
 * water = "OOHHHH"
 * 输出:
 * "HHOHHO"
 * 解释:
 * "HOHHHO", "OHHHHO", "HHOHOH", "HOHHOH", "OHHHOH", "HHOOHH", "HOHOHH" 和 "OHHOHH" 依然都是有效解。
 *  提示：
 * • 3 * n == water.length
 * • 1 <= n <= 20
 * • water[i] == 'O' or 'H'
 * • 输入字符串 water 中的 'H' 总数将会是 2 * n 。
 * • 输入字符串 water 中的 'O' 总数将会是 n 。
 * @date 2026/4/1 14:23
 */
public class Leetcode1117 {
    //Condition形式
    static class H2O {
        private String water;
        private final ReentrantLock LOCK = new ReentrantLock();
        private final Condition CON_H = LOCK.newCondition();
        private final Condition CON_O = LOCK.newCondition();
        private static volatile int stateO = 1, stateH = 2;
        private char[] waterArr;

        public H2O() {
        }

        public void hydrogen(Runnable releaseHydrogen) throws InterruptedException {
            try {
                LOCK.lock();
                // 【关键】H 凑够 2 个，唤醒 O！
                while (stateH == 0) {
                    CON_H.await();
                }
                // releaseHydrogen.run() outputs "H". Do not change or remove this line.
                releaseHydrogen.run();
                stateH--;
                if (stateH == 0) {
                    stateO++;
                    CON_O.signalAll();
                }
            } catch (Exception e) {
            } finally {
                LOCK.unlock();
            }

        }

        public void oxygen(Runnable releaseOxygen) throws InterruptedException {
            try {
                LOCK.lock();
                while (stateO == 0) {
                    CON_O.await();
                }
                // releaseOxygen.run() outputs "O". Do not change or remove this line.
                releaseOxygen.run();
                stateO--;
                if (stateO == 0) {
                    stateH += 2;
                    CON_H.signalAll();
                }
            } catch (Exception e) {
            } finally {
                LOCK.unlock();
            }

        }


        public H2O(String water) {
            this.water = water;
            this.waterArr = water.toCharArray();
        }

        public void createWater() {
            for (int i = 0; i < waterArr.length; i++) {
                if (waterArr[i] == 'H')
                    new Thread(() -> {
                        try {
                            hydrogen(() ->
                                    System.out.println("H")
                            );
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }).start();
                else
                    new Thread(() -> {
                        try {
                            oxygen(() ->
                                    System.out.println("O")
                            );
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }).start();
            }
        }
    }

    //Semaphore
    static class H2O1 {
        private String water;
        private static final Semaphore S_H = new Semaphore(2);
        private static final Semaphore S_O = new Semaphore(0);
        private char[] waterArr;

        public H2O1() {
        }

        public void hydrogen(Runnable releaseHydrogen) throws InterruptedException {
            S_H.acquire();
            // releaseHydrogen.run() outputs "H". Do not change or remove this line.
            releaseHydrogen.run();
            S_O.release();
        }

        public void oxygen(Runnable releaseOxygen) throws InterruptedException {
            S_O.acquire(2);
            // releaseOxygen.run() outputs "O". Do not change or remove this line.
            releaseOxygen.run();
            S_H.release(2);
        }


        public H2O1(String water) {
            this.water = water;
            this.waterArr = water.toCharArray();
        }

        public void createWater() {
            for (int i = 0; i < waterArr.length; i++) {
                if (waterArr[i] == 'H')
                    new Thread(() -> {
                        try {
                            hydrogen(() ->
                                    System.out.println("H")
                            );
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }).start();
                else
                    new Thread(() -> {
                        try {
                            oxygen(() ->
                                    System.out.println("O")
                            );
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }).start();
            }
        }
    }

    //Semaphore+CyclicBarrier
    static class H2O2 {
        private String water;
        private static final CyclicBarrier CB = new CyclicBarrier(3);
        private static final Semaphore S_H = new Semaphore(2);
        private static final Semaphore S_O = new Semaphore(1);
        private char[] waterArr;

        public H2O2() {
        }

        public void hydrogen(Runnable releaseHydrogen) throws InterruptedException {
            S_H.acquire();
            try {
                CB.await();
                releaseHydrogen.run();
            } catch (BrokenBarrierException e) {
                throw new RuntimeException(e);
            } finally {
            }
            S_H.release();
            // releaseHydrogen.run() outputs "H". Do not change or remove this line.

        }

        public void oxygen(Runnable releaseOxygen) throws InterruptedException {
            S_O.acquire();
            try {
                CB.await();
                releaseOxygen.run();

            } catch (BrokenBarrierException e) {
                throw new RuntimeException(e);
            } finally {
            }
            S_O.release();
            // releaseOxygen.run() outputs "O". Do not change or remove this line.
        }


        public H2O2(String water) {
            this.water = water;
            this.waterArr = water.toCharArray();
        }

        public void createWater() {
            for (int i = 0; i < waterArr.length; i++) {
                if (waterArr[i] == 'H')
                    new Thread(() -> {
                        try {
                            hydrogen(() ->
                                    System.out.println("H")
                            );
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }).start();
                else
                    new Thread(() -> {
                        try {
                            oxygen(() ->
                                    System.out.println("O")
                            );
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }).start();
            }
        }
    }

    //CountDownLatch
//    static class H2O3 {
//        private String water;
//        private  CountDownLatch CDL = new CountDownLatch(3);
//        private static final Semaphore S_H = new Semaphore(2);
//        private static final Semaphore S_O = new Semaphore(1);
//        private char[] waterArr;
//
//        public H2O3() {
//        }
//
//        public void hydrogen(Runnable releaseHydrogen) throws InterruptedException {
//            S_H.acquire();
//            CDL.countDown();
//            CDL.await();
//            releaseHydrogen.run();
//            S_H.release();
//            // releaseHydrogen.run() outputs "H". Do not change or remove this line.
//        }
//
//        public void oxygen(Runnable releaseOxygen) throws InterruptedException {
//            S_O.acquire();
//            CDL.countDown();
//            CDL.await();
//            releaseOxygen.run();
//
//            S_O.release();
//            if (CDL.getCount() == 0) {
//                CDL = new CountDownLatch(3);
//            }
//            // releaseOxygen.run() outputs "O". Do not change or remove this line.
//        }
//
//
//        public H2O3(String water) {
//            this.water = water;
//            this.waterArr = water.toCharArray();
//        }
//
//        public void createWater() {
//            for (int i = 0; i < waterArr.length; i++) {
//                if (waterArr[i] == 'H')
//                    new Thread(() -> {
//                        try {
//                            hydrogen(() ->
//                                    System.out.println("H")
//                            );
//                        } catch (InterruptedException e) {
//                            throw new RuntimeException(e);
//                        }
//                    }).start();
//                else
//                    new Thread(() -> {
//                        try {
//                            oxygen(() ->
//                                    System.out.println("O")
//                            );
//                        } catch (InterruptedException e) {
//                            throw new RuntimeException(e);
//                        }
//                    }).start();
//            }
//        }
//    }

    public static void main(String[] args) {
        H2O1 h2O = new H2O1("OHOOHOHHHHOHHOHHHH");
        h2O.createWater();
    }
}
