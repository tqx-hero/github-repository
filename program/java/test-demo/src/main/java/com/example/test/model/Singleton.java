package com.example.test.model;

/**
 * @author Administrator
 * @version 1.0
 * @description: 单例，饿汉式，在类加载时创建实例
 * @date 2026/2/24 18:37
 */
public class Singleton {

    private static final Singleton instance = new Singleton();

    public void Singleton() {
    }

    public static Singleton getInstance() {
        return instance;
    }

}
