package com.tqx.design.singleton;

/**
 * @author Administrator
 * @version 1.0
 * @description: 饿汉式单例，线程安全
 * @date 2026/3/15 22:52
 */
public class Hungry {
    private static Hungry instance = new Hungry();

    private Hungry() {
    }
    public static Hungry getInstance() {
        return instance;
    }
}
