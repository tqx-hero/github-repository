package com.spring.proxy.dromatic.cglib;

import org.springframework.cglib.proxy.MethodInterceptor;
import org.springframework.cglib.proxy.MethodProxy;

import java.lang.reflect.Method;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 23:49
 */
public class CallBackMethod implements MethodInterceptor {

    @Override
    public Object intercept(Object obj, Method method, Object[] args, MethodProxy proxy) throws Throwable {
        System.out.println("cglib代理执行前");
        Object o = proxy.invokeSuper(obj, args);
        System.out.println("cglib代理执行后");
        return o;
    }
}
