package com.tqx.thread.test;

/**
 * @author Administrator
 * @version 1.0
 * @description: 实际上运用的类加载机制，只有在使用时才会触发类加载，而且只会加载一次，也是一种懒汉模式
 * @date 2026/3/15 22:40
 */
public class StaticInnerClass {
    private StaticInnerClass() {
    }

    private static class InnerClass {
        private static StaticInnerClass instance = new StaticInnerClass();
    }

    public static StaticInnerClass getInstance() {
        return InnerClass.instance;
    }
}
