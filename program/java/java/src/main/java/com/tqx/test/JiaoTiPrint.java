package com.tqx.test;

import java.util.concurrent.Semaphore;

/**
 * @author Administrator
 * @version 1.0
 * @description: 实现交替打印
 * @date 2026/6/7 22:21
 */
public class JiaoTiPrint {
    //定义信号量，线程1拥有线程2的资源，t2需要等t1释放信号量，即执行V操作
    //同样t2用于t1的信号量，t1执行后需要等待t2执行V操作才能拥有信号量
    //首先执行的顺序取决于先给谁设置一个信号量初始值，
    //这里是先让t1执行，那么就先给t1设置sem=1，能够让它先执行一步P操作
    //后续就按照指定的P、V操作来顺序、交替执行
    private static final Semaphore s1 = new Semaphore(1);
    private static final Semaphore s2 = new Semaphore(0);

    private static class Thread1 extends Thread {
        @Override
        public void run() {
            for (int i = 1; i < 100; i += 2) {
                try {
                    s1.acquire();
                    System.out.println("线程1: " + i);
                    s2.release();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    private static class Thread2 extends Thread {
        @Override
        public void run() {
            for (int i = 2; i <= 100; i += 2) {
                try {
                    s2.acquire();
                    System.out.println("线程2: " + i);
                    s1.release();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread1 thread1 = new Thread1();
        Thread2 thread2 = new Thread2();
        thread1.start();
        thread2.start();
        thread2.join();
        thread1.join();
    }
}
