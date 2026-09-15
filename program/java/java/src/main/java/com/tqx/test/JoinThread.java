package com.tqx.test;

import java.util.concurrent.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: fork、join
 * @date 2026/6/7 22:39
 */
public class JoinThread {


    public static void main(String[] args) throws InterruptedException, ExecutionException {
        int[] arr = {10, 20, 30, 40, 50, 60, 70, 80};
        int res1 = 0;
        Callable<Integer> callable1 = () -> {
            int res = 0;
            for (int i = 0; i < 4; i++)
                res += arr[i];
            return res;
        };
        Callable<Integer> callable2 = () -> {
            int res = 0;
            for (int i = 4; i < 8; i++)
                res += arr[i];
            return res;
        };
        FutureTask<Integer> task1 = new FutureTask<>(callable1);
        FutureTask<Integer> task2 = new FutureTask<>(callable2);
        Thread thread1 = new Thread(task1);
        Thread thread2 = new Thread(task2);
        thread1.start();
        thread2.start();
        thread1.join();
        thread2.join();
        System.out.println("结果=："+(task1.get()+ task2.get()));
    }
}
