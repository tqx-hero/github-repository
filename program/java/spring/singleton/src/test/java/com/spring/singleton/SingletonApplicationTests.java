package com.spring.singleton;

import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;
import java.util.concurrent.TimeUnit;

@SpringBootTest
class SingletonApplicationTests {


    @Resource
    private Salary salary;

    @Test
    void contextLoads() throws InterruptedException {
        long begin = System.nanoTime();
        Thread thread1 = new Thread(() -> {
            salary.add(300);
            System.out.println("存钱后的余额====" + salary.salary);
//            System.out.println("存钱后的余额====" + salary.salary.getReference());
        }, "线程1");

        Thread thread2 = new Thread(() -> {
            salary.mit(300);
            System.out.println("取钱后的余额====" + salary.salary);
//            System.out.println("取钱后的余额====" + salary.salary.getReference());
        });

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();
        long end = System.nanoTime();
        System.out.println("总耗时=====" + TimeUnit.MILLISECONDS.toMillis(end - begin) + "ms");

    }

}
