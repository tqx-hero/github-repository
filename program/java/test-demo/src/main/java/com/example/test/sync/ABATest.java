package com.example.test.sync;

import java.util.concurrent.atomic.AtomicInteger;

/**
 * @author Administrator
 * @version 1.0
 * @description: AtomicInteger 的CAS出现ABA问题 ,具体防止策略为增加版本号（时间戳），以比较值+版本号的方法解决ABA问题
 * @date 2026/2/24 8:59
 */
public  final class ABATest {

    private static AtomicInteger count = new AtomicInteger(1);

    public static void main(String[] args) throws InterruptedException {
        Thread thread1 = new Thread(() -> {
            count.compareAndSet(1, 2);
            count.compareAndSet(2, 1);
        }, "线程1制造ABA");

        Thread thread2 = new Thread(() ->
                System.out.println("线程2是否修改成功: " + count.compareAndSet(1, 3))
                , "线程2");

        thread1.start();
        thread1.join();
        thread2.start();
        thread2.join();
        System.out.println(count.get());
    }
}
