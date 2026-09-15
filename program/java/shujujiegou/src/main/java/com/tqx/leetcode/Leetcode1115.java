package com.tqx.leetcode;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: 交替打印
 * 给你一个类：
 * class FooBar {
 * public void foo() {
 *     for (int i = 0; i < n; i++) {
 *       print("foo");
 *     }
 * }
 * <p>
 * public void bar() {
 *     for (int i = 0; i < n; i++) {
 *       print("bar");
 *     }
 * }
 * }
 * 两个不同的线程将会共用一个 FooBar 实例：
 * • 线程 A 将会调用 foo() 方法，而
 * • 线程 B 将会调用 bar() 方法
 * 请设计修改程序，以确保 "foobar" 被输出 n 次。 
 * 示例 1：
 * 输入：
 * n = 1
 * 输出：
 * "foobar"
 * 解释：
 * 这里有两个线程被异步启动。其中一个调用 foo() 方法, 另一个调用 bar() 方法，"foobar" 将被输出一次。
 * 示例 2：
 * 输入：
 * n = 2
 * 输出：
 * "foobarfoobar"
 * 解释：
 * "foobar" 将被输出两次。
 *  提示：
 * • 1 <= n <= 1000
 * @date 2026/4/1 10:16
 */
public class Leetcode1115 {

    //信号量方式
    static class FooBar {
        private int n;
        private static final Semaphore S1 = new Semaphore(0);
        private static final Semaphore S2 = new Semaphore(0);

        public FooBar(int n) {
            this.n = n;
        }

        public void foo(Runnable printFoo) throws InterruptedException {

            for (int i = 0; i < n; i++) {

                // printFoo.run() outputs "foo". Do not change or remove this line.
                printFoo.run();
                S2.release();
                S1.acquire();

            }
        }

        public void bar(Runnable printBar) throws InterruptedException {

            for (int i = 0; i < n; i++) {
                S2.acquire();
                // printBar.run() outputs "bar". Do not change or remove this line.
                printBar.run();
                S1.release();
            }
        }
    }

    //condition形式
    static class FooBar1 {
        private int n;
        private static final ReentrantLock LOCK = new ReentrantLock();
        private static final Condition CON = LOCK.newCondition();
        //        private static final Condition BAR = LOCK.newCondition();
        private volatile boolean flag = false;

        public FooBar1(int n) {
            this.n = n;
        }

        public void foo(Runnable printFoo) throws InterruptedException {

            for (int i = 0; i < n; i++) {
                try {
                    LOCK.lock();
                    while (flag) CON.await();
                    // printFoo.run() outputs "foo". Do not change or remove this line.
                    printFoo.run();
                    flag = true;
                    CON.signalAll();
                } catch (Exception e) {
                } finally {
                    LOCK.unlock();
                }


            }
        }

        public void bar(Runnable printBar) throws InterruptedException {

            for (int i = 0; i < n; i++) {
                try {
                    LOCK.lock();
                    while (!flag) CON.await();
                    // printBar.run() outputs "bar". Do not change or remove this line.
                    printBar.run();
                    flag = false;
                    CON.signalAll();
                } catch (Exception e) {
                } finally {
                    LOCK.unlock();
                }

            }
        }
    }

    //CyclicBarrier方式
    static class FooBar2 {
        private int n;
        private static final CyclicBarrier CYC = new CyclicBarrier(2);
        private static volatile boolean flag = true;

        public FooBar2(int n) {
            this.n = n;
        }

        public void foo(Runnable printFoo) throws InterruptedException {

            for (int i = 0; i < n; i++) {
                try {
                    while (!flag)
                        CYC.await();
                    // printFoo.run() outputs "foo". Do not change or remove this line.
                    printFoo.run();
                    flag = false;
                    CYC.await();
                } catch (BrokenBarrierException e) {
                    throw new RuntimeException(e);
                }

            }
        }

        public void bar(Runnable printBar) throws InterruptedException {

            for (int i = 0; i < n; i++) {
                try {
                    while (flag)
                        CYC.await();
                    // printBar.run() outputs "bar". Do not change or remove this line.
                    printBar.run();
                    flag = true;
                    CYC.await();
                } catch (BrokenBarrierException e) {
                    throw new RuntimeException(e);
                }

            }
        }
    }

    //CountDownLatch的用法，注意：CountDownLatch是一次性的，计数归零后需要
    //重新new实例
    static class FooBar3 {
        private int n;
        private CountDownLatch l1;
        private CountDownLatch l2;


        public FooBar3(int n) {
            this.n = n;
            l1 = new CountDownLatch(0);
            l2 = new CountDownLatch(1);
        }

        public void foo(Runnable printFoo) throws InterruptedException {

            for (int i = 0; i < n; i++) {
                //expect 0
                // printFoo.run() outputs "foo". Do not change or remove this line.
                l1.await();
                printFoo.run();
                l1 = new CountDownLatch(1);
                l2.countDown();
            }
        }

        public void bar(Runnable printBar) throws InterruptedException {

            for (int i = 0; i < n; i++) {
                //expect 1
                l2.await();
                // printBar.run() outputs "bar". Do not change or remove this line.
                printBar.run();
                l2 = new CountDownLatch(1);
                l1.countDown();
            }
        }
    }

    public static void main(String[] args) {
        FooBar3 bar = new FooBar3(5);
        new Thread(() -> {
            try {
                bar.foo(() -> {
                    System.out.println("foo");
                });
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }).start();
        new Thread(() -> {
            try {
                bar.bar(() -> {
                    System.out.println("bar");
                });
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }).start();
    }


}
