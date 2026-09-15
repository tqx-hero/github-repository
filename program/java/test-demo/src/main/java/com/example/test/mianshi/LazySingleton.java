package com.example.test.mianshi;

/**
 * @author Administrator
 * @version 1.0
 * @description: 懒汉式单例
 * @date 2026/3/3 20:16
 */
public class LazySingleton {
    //生成实例对象
    private static volatile LazySingleton instance;

    //私有化构造方法
    private LazySingleton() {
    }

    //提供实力生成方法，当调用时先判断是否已经创建实例，没有则创建，有则直接调用.
    public static LazySingleton getInstance() {

        if (instance == null) {
            synchronized (LazySingleton.class) {
                if (instance == null) {
                    instance = new LazySingleton();
                }
            }
        }
        return instance;
    }

}
