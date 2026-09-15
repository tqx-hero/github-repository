package com.tqx.thread.local;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 16:12
 */
public class ChildThreadLocal {

    public static void main(String[] args) {
        ThreadLocal<String> local = new InheritableThreadLocal<>();
        local.set("张三");
        Thread thread = new Thread(() -> {
            String s = local.get();
            System.out.println(s);
        });
        thread.start();
    }
}
