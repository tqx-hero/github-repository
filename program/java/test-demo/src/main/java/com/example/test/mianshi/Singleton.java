package com.example.test.mianshi;

/**
 * @author Administrator
 * @version 1.0
 * @description: 单例, JVM一启动就会生成实例。线程安全
 * @date 2026/3/3 20:02
 */
public class Singleton {

    //创建内存中独一份的实例，静态全局可访问、常量不可变
    public static final Singleton INSTANCE = new Singleton();

    //私有化构造方法，防止外部访问以构造器方式创建对象
    private Singleton() {
    }

    //提供静态方法，将该单例通过此方式暴漏给外部
    public static Singleton getInstance() {
        return INSTANCE;
    }
}
