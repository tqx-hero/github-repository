package com.spring.proxy.dromatic.jdk;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 23:16
 */
public class JDKDemo implements IJDKDemo {
    @Override
    public void metting(String name) {
        System.out.println("boss接见了 " + name);
    }
}
