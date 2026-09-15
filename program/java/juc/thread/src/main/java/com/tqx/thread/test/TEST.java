package com.tqx.thread.test;

import java.util.concurrent.locks.LockSupport;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 22:45
 */
public class TEST {
    public static void main(String[] args) {
        StaticInnerClass instance = StaticInnerClass.getInstance();
        StaticInnerClass instance1 = StaticInnerClass.getInstance();
        System.out.println(instance == instance1);
    }
}
