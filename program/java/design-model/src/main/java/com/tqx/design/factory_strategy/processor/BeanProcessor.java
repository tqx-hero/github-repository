package com.tqx.design.factory_strategy.processor;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/22 9:32
 */
public class BeanProcessor implements ProxyProcessor {

    private static class BeanProcessorInnerClass {
        private static final BeanProcessor INSTANCE = new BeanProcessor();
    }

    public static BeanProcessor getInstance() {
        return BeanProcessorInnerClass.INSTANCE;
    }

    private BeanProcessor() {
    }

    @Override
    public void beforeProcessor() {
        System.out.println("前置处理");
    }

    @Override
    public void afterProcessor() {
        System.out.println("后置处理");
    }
}
