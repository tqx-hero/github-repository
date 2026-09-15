package com.tqx.thread.aqs;

import java.util.concurrent.TimeUnit;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/17 14:21
 */
public class Test {

    private static Lock lock = new Lock();

    private static int num = 1000;

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < 1000; i++) {
            new Thread(() -> {
                try {
                    lock.lock();
                    num--;
                } catch (Exception e) {
                } finally {
                    lock.unlock();
                }
            }).start();
        }

//        new Thread(() -> {
//            try {
//                lock.lock();
//                num--;
//            } catch (Exception e) {
//            } finally {
//                lock.unlock();
//            }
//        }).start();

        TimeUnit.SECONDS.sleep(20);

        System.out.println("数量=" + num);

        System.out.println("队列==" + lock.getQueue());
    }
}
