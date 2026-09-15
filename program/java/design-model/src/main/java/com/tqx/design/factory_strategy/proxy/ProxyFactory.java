package com.tqx.design.factory_strategy.proxy;

import com.tqx.design.factory_strategy.ann.AOP;
import com.tqx.design.factory_strategy.util.AnnotationUtils;
import org.springframework.cglib.proxy.Callback;

import java.lang.annotation.Annotation;

public interface ProxyFactory<T> {
    Class PROXY_ANNOTATION = AOP.class;

    T createProxy(Class<T> clazz);

    static boolean needAop(Class clazz) {
        AOP a = (AOP) clazz.getAnnotation(PROXY_ANNOTATION);
        return !clazz.isAnnotation() && AnnotationUtils.contaions(clazz, PROXY_ANNOTATION, "enhance", a.enhance())
                ;
    }

    ProxyFactory setBack(Callback back);
}
