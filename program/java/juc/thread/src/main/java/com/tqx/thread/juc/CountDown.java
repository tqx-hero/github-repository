package com.tqx.thread.juc;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

/**
 * @author Administrator
 * @version 1.0
 * @description: CountDownLatch实现让多线程按照一定顺序先后执行。
 * @date 2026/3/18 22:01
 */
public class CountDown {

    private static CountDownLatch latch = new CountDownLatch(5);

    public static void main(String[] args) throws InterruptedException {

        for (int i = 5; i < 10; i++) {
            final int s = i;
            new Thread(() -> {
                try {
                    latch.await();
                    System.out.println("num = " + s);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }).start();
        }
//        TimeUnit.SECONDS.sleep(2);
        for (int i = 0; i < 5; i++) {
            final int s = i;
            new Thread(() -> {
                System.out.println("num = " + s);
                latch.countDown();
            }).start();
        }


//        latch.countDown();
//        latch.countDown();
//        latch.countDown();

    }

}
