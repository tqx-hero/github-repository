package com.tqx.design.factory_strategy.aop;

import com.tqx.design.factory_strategy.proxy.ProxyFactory;
import org.springframework.cglib.proxy.Callback;
import org.springframework.cglib.proxy.Enhancer;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/22 8:47
 */
public class AopProxy implements ProxyFactory {

    private Callback back;

    private AopProxy() {
    }

    private static class AopProxyInnerClass {
        private static AopProxy INSTANCE = new AopProxy();
    }

    public static AopProxy getInstance() {
        return AopProxyInnerClass.INSTANCE;
    }

    public ProxyFactory setBack(Callback back) {
        this.back = back;
        return this;
    }

    @Override
    public Object createProxy(Class clazz) {
        Enhancer enhancer = new Enhancer();
        enhancer.setSuperclass(clazz);
        enhancer.setCallback(back);
        return enhancer.create();
    }
}
