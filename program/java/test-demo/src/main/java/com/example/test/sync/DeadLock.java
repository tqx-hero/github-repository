package com.example.test.sync;

/**
 * @author Administrator
 * @version 1.0
 * @description: 死锁产生的4个必要条件：
 * 1、互斥条件： 锁的资源只能被一个线程持有（synchronized,ReentrantLock等都是互斥锁）；
 * 2、循环等待条件：多个线程之间你中有我，我中有你的循环等待链
 * 3、持有并等待条件： 多个线程持有一个锁的同时，等待获取其他的锁
 * 4、不可剥夺条件：线程持有的锁不能被其他线程剥夺，只能自己主动释放
 * @date 2026/2/24 12:00
 */
public class DeadLock {

    private final static Object object1 = new Object();
    private static final Object object2 = new Object();

    static void thread1() {
        new Thread(() -> {
            synchronized (object1) {

                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {

                    e.printStackTrace();
                }
                System.out.println(Thread.currentThread().getName() + " 正在运行......");
                synchronized (object2) {
                    System.out.println(Thread.currentThread().getName() + " 正在运行");
                }
            }
        }, "线程1").start();

    }


    static void thread2() {
        new Thread(() -> {
            synchronized (object2) {

                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {

                    e.printStackTrace();
                }
                System.out.println(Thread.currentThread().getName() + " 正在运行......");
                synchronized (object1) {
                    System.out.println(Thread.currentThread().getName() + " 正在运行");
                }
            }
        }, "线程2").start();

    }

    public static void main(String[] args) {
        thread1();
        thread2();
    }
}
