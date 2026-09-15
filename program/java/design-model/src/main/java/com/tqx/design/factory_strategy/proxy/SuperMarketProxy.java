package com.tqx.design.factory_strategy.proxy;

import com.tqx.design.AnnotationScannerFactory;
import com.tqx.design.factory_strategy.process.SimpleBeanPostProssor;
import org.springframework.cglib.proxy.Enhancer;

import java.util.Set;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 23:27
 */
public class SuperMarketProxy {

    private AnnotationScannerFactory scanner;

    private SimpleBeanPostProssor processor;

    {
        scanner = AnnotationScannerFactory.getInstance();
    }

    void beforeProcessor() {

    }

    void afterProcessor() {

    }

//    public void getProxy() {
//        Set<Class<?>> set = scanner.getClassSet();
//        if (!set.isEmpty()) {
//            set.forEach(c -> {
//                ProxyFactory p = () -> {
//                    Enhancer enhancer = new Enhancer();
//                    enhancer.setSuperclass(c);
//                    enhancer.setCallback(
//                            (obj, method, args,
//                             proxy) -> {
//                                //前置处理
//                                beforeProcessor();
//                                proxy.invoke(obj, args);
//                                //后置处理
//                                afterProcessor();
//                            }
//                    );
//                    c.getClass() o = (c.getClass()) enhancer.create();
//                    enhancer.
//                    return null;
//                };
//            });
//        }
//    }

    public static void main(String[] args) {

    }
}
