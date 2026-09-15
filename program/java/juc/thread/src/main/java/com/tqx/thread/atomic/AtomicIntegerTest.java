package com.tqx.thread.atomic;

import java.util.Set;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 18:44
 */
public class AtomicIntegerTest {
    public static  AtomicInteger total = new AtomicInteger(40000);

    public static void main(String[] args) {

        ThreadPoolExecutor executor = new ThreadPoolExecutor(12, 200, 10, TimeUnit.SECONDS
                , new ArrayBlockingQueue<>(2000)
                , new ThreadPoolExecutor.CallerRunsPolicy());
        try {
            int num = 0;
            for (int i = 0; i < 100000; i++) {
                Future<?> future = executor.submit(() -> {
                    Thread.sleep(200);
                    if (total.get() <= 0)
                        return 0;
                    int oldValue, newValue;
                    do {
                        oldValue = total.get();
                        newValue = oldValue - 1;
                    } while (!total.compareAndSet(oldValue, newValue));
                    System.out.println("用户：" + Thread.currentThread().getName() + "获取一份礼品");
                    return 1;
                });
                if (future.get() instanceof Integer) {
                    num += (Integer) future.get();
                }
            }
            System.out.println("统计已销售的礼品数量=" + num);
        } catch (Exception e) {
        } finally {
            executor.shutdown();
        }


    }
}
