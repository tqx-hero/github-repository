package com.tqx.juc.singleton;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/13 15:52
 */
public class LazySingleton {
    private static LazySingleton instance;

    private LazySingleton() {
    }

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
