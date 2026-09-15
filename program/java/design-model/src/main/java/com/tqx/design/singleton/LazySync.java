package com.tqx.design.singleton;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 22:58
 */
public class LazySync {

    private LazySync() {
    }

    private static LazySync instance;

    public static LazySync getInstance() {
        if (instance == null) {
            synchronized (LazySync.class) {
                if (instance == null) {
                    instance = new LazySync();
                }
            }
        }
        return instance;
    }
}
