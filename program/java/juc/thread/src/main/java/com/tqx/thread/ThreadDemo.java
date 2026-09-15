package com.tqx.thread;

import java.util.concurrent.TimeUnit;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/13 18:34
 */
public class ThreadDemo {
    public static void main(String[] args) throws InterruptedException {

        //创建线程的方式
        Thread t1 = new Thread(() ->
        {
            System.out.println("线程1创建成功");
            Thread.yield();
//            try {
//                TimeUnit.MILLISECONDS.sleep(100);
            for (int i = 1; i <= 10; i++) {
                System.out.println(Thread.currentThread().getName() + ": " + i);
            }
//            } catch (InterruptedException e) {
//                throw new RuntimeException(e);
//            }
        }
                , "线程1");


        Thread t2 = new Thread(() -> {
            System.out.println("线程创建成功2");
            for (int i = 1; i <= 10; i++) {
                System.out.println(Thread.currentThread().getName() + ": " + i);
            }
        }, "线程2");


        //设置权限
//        t2.setPriority(Thread.MIN_PRIORITY);
//        t1.setPriority(Thread.MAX_PRIORITY);
        t1.start();
        t2.start();
//        Thread.yield();
//        System.out.println("权限等级=" + t1.getPriority());
        System.out.println("主线程");
        t1.join();
        t2.join();
    }
}
