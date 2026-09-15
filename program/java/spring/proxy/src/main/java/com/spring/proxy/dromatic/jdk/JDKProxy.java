package com.spring.proxy.dromatic.jdk;

import com.spring.proxy.dromatic.ts.jdk.JDKD;

import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.lang.reflect.Proxy;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 23:17
 */
public class JDKProxy {

    //    public static void main(String[] args) {
//        //设置该属性就可以将jdk动态代理生成的代理类导出到{当前目录}/jdk/proxy1下面
//        System.getProperties().put("jdk.proxy.ProxyGenerator.saveGeneratedFiles", "true");
//        //生成JDK代理对象
//        IJDKDemo o = (IJDKDemo) Proxy.newProxyInstance(JDKDemo.class.getClassLoader(),
//                JDKDemo.class.getInterfaces(),
//                new JDKInvokerHandler(new JDKDemo()));
//
//        o.metting("张三");
//    }
    public static void main(String[] args) throws Throwable {
        //设置该属性就可以将jdk动态代理生成的代理类导出到{当前目录}/jdk/proxy1下面
        System.getProperties().put("sun.misc.ProxyGenerator.saveGeneratedFiles", "true");
        Class<?> aClass = Proxy.getProxyClass(IJDKDemo.class.getClassLoader(), IJDKDemo.class);
        System.out.println("代理类名：" + aClass.getName());
//        IJDKDemo o = (IJDKDemo) Proxy.newProxyInstance(JDKDemo.class.getClassLoader(),
//                JDKDemo.class.getInterfaces(),
//                new JDKInvokerHandler(new JDKDemo()));
//
//        o.metting("张三");
    }
}
