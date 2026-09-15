package com.tqx.thread.local;

import org.springframework.scheduling.concurrent.DefaultManagedAwareThreadFactory;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * @author Administrator
 * @version 1.0
 * @description: 测试ThreadLocal内存泄漏
 * @date 2026/3/15 15:26
 */
public class ThreadLocalTest {

    public static ThreadLocal<User> local = new ThreadLocal<>();

    public static void main(String[] args) {

        ThreadPoolExecutor executor = new ThreadPoolExecutor(12, 200, 10, TimeUnit.SECONDS
                , new ArrayBlockingQueue<>(300)
                , new DefaultManagedAwareThreadFactory(),
                new ThreadPoolExecutor.CallerRunsPolicy());

        try {
            for (int i = 0; i < 40; i++) {
                executor.execute(() -> {
                    try {
                        local.set(new User());
                    } catch (Exception e) {
                    } finally {
                        local.remove();

                    }
                });
            }
        } catch (Exception e) {
        } finally {
            executor.shutdown();
        }
    }
}
