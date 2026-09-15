package com.tqx.thread.pool;

import org.springframework.scheduling.concurrent.CustomizableThreadFactory;

import java.util.concurrent.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 9:01
 */
public class ThreadPool {

    //    public static void main(String[] args) {
//        ThreadPoolExecutor executor = new ThreadPoolExecutor(13, 200, 10, TimeUnit.SECONDS
//                , new ArrayBlockingQueue<>(200),
//                new CustomizableThreadFactory()
//                , new ThreadPoolExecutor.CallerRunsPolicy());
//        try {
//            for (int i = 0; i < 200; i++) {
//                final int finalI = i;
//                FutureTask<Integer> futureTask = new FutureTask<>(() -> finalI);
//                executor.execute(futureTask);
//                System.out.println(Thread.currentThread().getName() + ":" + futureTask.get());
//            }
//        } catch (Exception e) {
//            e.printStackTrace();
//        } finally {
//            executor.shutdown();
//        }
//    }
    public static void main(String[] args) {
        ThreadPoolExecutor executor = new ThreadPoolExecutor(13, 200, 10, TimeUnit.SECONDS
                , new ArrayBlockingQueue<>(200),
                new CustomizableThreadFactory()
                , new ThreadPoolExecutor.CallerRunsPolicy());
        try {
            for (int i = 0; i < 200; i++) {
                final int finalI = i;
//                Future<Integer> future = executor.submit(() -> finalI);
                Future<?> future = executor.submit(() -> {
                    System.out.println(finalI);
                    return finalI;
                });
                System.out.println("线程返回值==" + future.get());
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            executor.shutdown();
        }
    }
}
