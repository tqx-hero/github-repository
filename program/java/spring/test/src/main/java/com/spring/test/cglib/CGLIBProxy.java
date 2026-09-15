package com.spring.test.cglib;

import org.springframework.cglib.core.DebuggingClassWriter;
import org.springframework.cglib.proxy.Enhancer;
import org.springframework.cglib.proxy.InvocationHandler;
import org.springframework.cglib.proxy.MethodInterceptor;
import org.springframework.cglib.proxy.MethodProxy;

import java.io.File;
import java.lang.reflect.Method;


/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/11 8:49
 */
public class CGLIBProxy {

    public static void main(String[] args) {
        Enhancer enhancer = new Enhancer();
        enhancer.setSuperclass(CGLIBBoss.class);
        CGLIBBoss boss = new CGLIBBoss();
        //设置cgljb文件导出
//        String savePath = System.getProperty("user.dir") + File.separator + "cglib_proxy_classes";
//        System.setProperty(DebuggingClassWriter.DEBUG_LOCATION_PROPERTY, savePath);
        enhancer.setCallback((MethodInterceptor) (obj, method, args1, proxy) -> {
            System.out.println("cglib代理增强--执行方法前");
//            Object o = proxy.invokeSuper(obj, args1);
            Object o = proxy.invoke(boss, args1);
            System.out.println("cglib代理增强--执行方法后");
            return o;
        });
        CGLIBBoss object = (CGLIBBoss) enhancer.create();
        object.say("曹操");
    }
}

