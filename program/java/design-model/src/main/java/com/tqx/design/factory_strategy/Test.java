package com.tqx.design.factory_strategy;

import com.tqx.design.AnnotationScannerFactory;

/**
 * @author Administrator
 * @version 1.0
 * @description: 单例模式+工厂模式+策略模式实现spring管理单例
 *  由于使用了CGLIB动态代理，jdk17将其进行了模块化，需要手动添加启动参数打开访问权限：
 *      --add-opens=java.base/java.lang=ALL-UNNAMED
 *      --add-opens=java.base/java.lang.reflect=ALL-UNNAMED
 *      --add-opens=java.base/java.lang.invoke=ALL-UNNAMED
 *      --add-opens=java.base/jdk.internal.loader=ALL-UNNAMED
 * @date 2026/3/21 22:13
 */
public class Test {

    public static void main(String[] args) {
//        SuperMarketFactory.getInstance()
//                .setName(SuperMarkets.WOLNA.get())
//                .getSuperMartStrategy()
//                .disCount();
//        SuperMarketFactory.getInstance()
//                .setName(SuperMarkets.YINZUO.get())
//                .getSuperMartStrategy()
//                .disCount();

        WolmaStrategy o = (WolmaStrategy) AnnotationScannerFactory.getInstance()
                .getBean(SuperMarkets.WOLNA.get());
        o.disCount();

    }
}
