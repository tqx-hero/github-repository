package com.tqx.design.singleton;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 23:01
 */
public class InnerClass {
    private InnerClass() {
    }

    private static class Inner {
        private static InnerClass instance = new InnerClass();
    }

    public static InnerClass getInstance() {
        return Inner.instance;
    }
}
