package com.tqx.thread.self;

import org.springframework.scheduling.concurrent.DefaultManagedAwareThreadFactory;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.FutureTask;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 12:04
 */
public class TestSelfThreadPoolExecutor {

    public static void main(String[] args) {
        SelfThreadPoolExecutor executor = new SelfThreadPoolExecutor(12, 200, new ArrayBlockingQueue<>(100)
                , new DefaultManagedAwareThreadFactory());

        int count = 0;
        try {
            for (int i = 0; i < 2000; i++) {
                final int finalI = i;
                final int cn = 1;
                FutureTask<Integer> task = new FutureTask<>(() -> {
                    System.out.println(Thread.currentThread().getName() + " : " + finalI);
                    return cn;
                });
                executor.execute(task);
                count += task.get();
            }
            System.out.println("最终统计数量=" + count);
            System.out.println("核心线程数还剩：" + SelfThreadPoolExecutor.getThreadNum());
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            executor.shutDown();
        }
    }
}
