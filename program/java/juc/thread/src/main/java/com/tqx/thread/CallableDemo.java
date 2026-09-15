package com.tqx.thread;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.FutureTask;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/14 22:55
 */
public class CallableDemo {

    public static void main(String[] args) {
        FutureTask<Integer> futureTask = new FutureTask<>(() -> {
            int s = 0;
            for (int i = 0; i < 100; i++) {
                s += i;
            }
            return s;
        });

        Thread thread = new Thread(futureTask);
        thread.start();
        try {
            System.out.println("返回值==" + futureTask.get());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        System.out.println("主线程执行结束");
    }
}
