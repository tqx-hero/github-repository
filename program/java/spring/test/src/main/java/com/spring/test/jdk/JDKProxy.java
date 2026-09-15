package com.spring.test.jdk;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

/**
 * @author Administrator
 * @version 1.0
 * @description: jdk动态代理
 * @date 2026/3/11 8:43
 */
public class JDKProxy {
    public static void main(String[] args) {
//        System.getProperties().put("jdk.proxy.ProxyGenerator.saveGeneratedFiles", "true");
        IJDKBoss boss = new JDKBoss();
        IJDKBoss p = (IJDKBoss) Proxy.newProxyInstance(IJDKBoss.class.getClassLoader(), JDKBoss.class.getInterfaces()
                , (Object proxy, Method method, Object[] args1) -> {
                    System.out.println("代理增强--执行方法前");
                    Object o = method.invoke(boss, args1);
                    System.out.println("代理增强--执行方法后");
                    return o;
                });
        p.say("赵云");
    }
}
