package com.spring.proxy.dromatic.cglib;

import org.springframework.cglib.proxy.Enhancer;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 23:42
 */
public class CGLIBProxy {
    public static void main(String[] args) {
        Enhancer enhancer = new Enhancer();
        enhancer.setSuperclass(CGLIBBoss.class);
        enhancer.setCallback(new CallBackMethod());
        CGLIBBoss proxy = (CGLIBBoss) enhancer.create();
        proxy.metting("张三");
    }
}
