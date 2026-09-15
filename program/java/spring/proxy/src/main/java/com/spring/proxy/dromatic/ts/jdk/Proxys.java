package com.spring.proxy.dromatic.ts.jdk;

import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 19:37
 */
public class Proxys {

    public static void main(String[] args) {
        System.getProperties().put("jdk.proxy.ProxyGenerator.saveGeneratedFiles", "true");
        JDPDemo obj = new JDPDemo();
        JDKD o = (JDKD) Proxy.newProxyInstance(JDKD.class.getClassLoader(), JDPDemo.class.getInterfaces(),
                (proxy, method, arg) ->
                        method.invoke(obj, arg)
        );
        o.say();
    }
}
