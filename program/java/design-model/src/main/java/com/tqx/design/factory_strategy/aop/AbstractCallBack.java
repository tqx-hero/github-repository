package com.tqx.design.factory_strategy.aop;


import com.tqx.design.factory_strategy.processor.ProxyProcessor;
import org.springframework.cglib.proxy.MethodInterceptor;
import org.springframework.cglib.proxy.MethodProxy;

import java.lang.reflect.Method;

/**
 * @author Administrator
 * @version 1.0
 * @description:
 * @date 2026/3/22 9:21
 */
public class AbstractCallBack implements MethodInterceptor {

    private ProxyProcessor processor;

    public AbstractCallBack setProcessor(ProxyProcessor processor) {
        this.processor = processor;
        return this;
    }

    private static class CallBackInnerClass {
        private static final AbstractCallBack INSTANCE = new AbstractCallBack();
    }

    public static AbstractCallBack getInstance() {
        return CallBackInnerClass.INSTANCE;
    }

    void beforeProcessor() {
        processor.beforeProcessor();
    }

    void afterProcessor() {
        processor.afterProcessor();
    }

    @Override
    public Object intercept(Object obj, Method method, Object[] args, MethodProxy proxy) throws Throwable {
        beforeProcessor();
        Object o = proxy.invokeSuper(obj, args);
        afterProcessor();
        return o;
    }
}
