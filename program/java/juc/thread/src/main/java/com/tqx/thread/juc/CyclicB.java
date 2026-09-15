package com.tqx.thread.juc;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/18 22:14
 */
public class CyclicB {

    private static CyclicBarrier b = new CyclicBarrier(3);

    public static void main(String[] args) {
        for (int i = 0; i < 3; i++) {
            final int num = i;
            new Thread(() -> {
                try {
                    b.await();
                    System.out.println("num=" + num);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                } catch (BrokenBarrierException e) {
                    throw new RuntimeException(e);
                }
            }).start();
        }
    }
}
