package com.spring.proxy.dromatic.ts.jdk;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 19:36
 */
public class JDPDemo implements JDKD {
    @Override
    public void say() {
        System.out.println("say");
    }

    public void add() {
        System.out.println("add");
    }
}
