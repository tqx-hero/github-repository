package com.spring.proxy.staticp;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 23:10
 */
public class StaticProxyTest {

    public static void main(String[] args) {
        Boss proxy = new StaticProxy();
        proxy.metting("张三");
    }
}
