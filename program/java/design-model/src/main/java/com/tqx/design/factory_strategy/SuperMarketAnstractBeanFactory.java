package com.tqx.design.factory_strategy;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/22 8:32
 */
public abstract class SuperMarketAnstractBeanFactory implements SuperMarketAbstractFactory {

    @Override
    public SuperMartStrategy getSuperMartStrategy() {
        return null;
    }

    protected abstract Object getBean(String className);

}
