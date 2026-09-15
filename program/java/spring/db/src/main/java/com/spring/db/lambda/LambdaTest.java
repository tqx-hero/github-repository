package com.spring.db.lambda;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/13 9:26
 */
public class LambdaTest {

    public static void main(String[] args) {
        Runnable runnable = () -> System.out.println("线程启动");
        runnable.run();
    }
}
