package com.tqx.design.singleton;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 22:55
 */
public class LazyNoSync {

    private static LazyNoSync instance;

    private LazyNoSync() {
    }

    public static LazyNoSync getInstance() {
        if (instance == null) {
            instance = new LazyNoSync();
        }
        return instance;
    }
}
