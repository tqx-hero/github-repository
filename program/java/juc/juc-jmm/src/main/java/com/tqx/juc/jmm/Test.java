package com.tqx.juc.jmm;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/13 13:45
 */
public class Test {

    private static  boolean flag = false;

    public static void main(String[] args) throws InterruptedException {
        new Thread(() -> {
            System.out.println("线程1启动");
            while (!flag) {

            }
            System.out.println("线程1结束");
        }).start();

        Thread.sleep(5000);

        new Thread(() -> {
            System.out.println("线程2启动");
            flag = true;
            System.out.println("线程2结束");
        }).start();
    }
}
