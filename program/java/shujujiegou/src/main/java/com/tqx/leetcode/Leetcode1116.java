package com.tqx.leetcode;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.IntConsumer;

/**
 * @author Administrator
 * @version 1.0
 * @description: 打印0与奇偶数
 * 现有函数 printNumber 可以用一个整数参数调用，并输出该整数到控制台。
 * • 例如，调用 printNumber(7) 将会输出 7 到控制台。
 * 给你类 ZeroEvenOdd 的一个实例，该类中有三个函数：zero、even 和 odd 。ZeroEvenOdd 的相同实例将会传递给三个不同线程：
 * • 线程 A：调用 zero() ，只输出 0
 * • 线程 B：调用 even() ，只输出偶数
 * • 线程 C：调用 odd() ，只输出奇数
 * 修改给出的类，以输出序列 "010203040506..." ，其中序列的长度必须为 2n 。
 * 实现 ZeroEvenOdd 类：
 * • ZeroEvenOdd(int n) 用数字 n 初始化对象，表示需要输出的数。
 * • void zero(printNumber) 调用 printNumber 以输出一个 0 。
 * • void even(printNumber) 调用printNumber 以输出偶数。
 * • void odd(printNumber) 调用 printNumber 以输出奇数。 
 * 示例 1：
 * 输入：
 * n = 2
 * 输出：
 * "0102"
 * 解释：
 * 三条线程异步执行，其中一个调用 zero()，另一个线程调用 even()，最后一个线程调用odd()。正确的输出为 "0102"。
 * 示例 2：
 * 输入：
 * n = 5
 * 输出：
 * "0102030405"
 *  提示：
 * • 1 <= n <= 1000
 * @date 2026/4/1 12:08
 */
public class Leetcode1116 {

    static class ZeroEvenOdd {
        private int n;
        private final Semaphore S0 = new Semaphore(0);
        private final Semaphore S1 = new Semaphore(0);
        private final Semaphore S2 = new Semaphore(0);
        private final AtomicInteger currentNum = new AtomicInteger();

        public ZeroEvenOdd(int n) {
            this.n = n;
        }

        // printNumber.accept(x) outputs "x", where x is an integer.
        public void zero(IntConsumer printNumber) throws InterruptedException {
            for (int i = 0; i < n; i++) {
                printNumber.accept(0);
                //偶数唤醒调用奇数线程
                //奇数唤醒调用偶数的线程
                currentNum.incrementAndGet();
                if (i % 2 == 1)
                    S2.release();
                else
                    S1.release();
                if (currentNum.get() == n)
                    break;
                S0.acquire();
            }
        }

        public void even(IntConsumer printNumber) throws InterruptedException {
            for (int i = 2; i <= n; i += 2) {
                S2.acquire();
                printNumber.accept(currentNum.get());
                S0.release();
//                if (currentNum.get() + 1 >= n)
//                    return;
            }
        }

        public void odd(IntConsumer printNumber) throws InterruptedException {
            for (int i = 1; i <= n; i += 2) {
                S1.acquire();
                printNumber.accept(currentNum.get());
                S0.release();
//                if (currentNum.get() + 1 >= n)
//                    return;
            }
        }
    }

    //yield方式,会导致CPU利用率飙高，
    // 仅适用于等待时间非常短的场景，慎用
    static class ZeroEvenOdd1 {
        private int n;
        private volatile boolean isZero;
        private volatile int config;

        public ZeroEvenOdd1(int n) {
            this.n = n;
            this.isZero = true;
            this.config = 1;
        }

        // printNumber.accept(x) outputs "x", where x is an integer.
        public void zero(IntConsumer printNumber) throws InterruptedException {

            for (int i = 0; i < n; i++) {
                while (!isZero)
                    Thread.yield();
                printNumber.accept(0);
                isZero = false;
            }

        }

        //偶数
        public void even(IntConsumer printNumber) throws InterruptedException {
            for (int i = 2; i <= n; i += 2) {
                while (isZero || config == 1)
                    Thread.yield();
                printNumber.accept(i);
                isZero = true;
                config = 1;
            }
        }

        public void odd(IntConsumer printNumber) throws InterruptedException {
            for (int i = 1; i <= n; i += 2) {
                while (isZero || config == 2)
                    Thread.yield();
                printNumber.accept(i);
                isZero = true;
                config = 2;
            }
        }
    }

    public static void main(String[] args) {
        ZeroEvenOdd1 z = new ZeroEvenOdd1(6);
        new Thread(() -> {
            try {
                z.zero(System.out::println);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }).start();
        new Thread(() -> {
            try {
                z.even(System.out::println);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }).start();
        new Thread(() -> {
            try {
                z.odd(System.out::println);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }).start();
    }
}
