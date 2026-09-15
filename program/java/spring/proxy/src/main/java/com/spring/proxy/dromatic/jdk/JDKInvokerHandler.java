package com.spring.proxy.dromatic.jdk;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 23:21
 */
public class JDKInvokerHandler implements InvocationHandler {
    private Object target;

    public JDKInvokerHandler(Object target) {
        this.target = target;
    }
    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        System.out.println("调用方法前");
        Object o = method.invoke(target, args);
        System.out.println("调用方法后");
        return o;
    }
}
