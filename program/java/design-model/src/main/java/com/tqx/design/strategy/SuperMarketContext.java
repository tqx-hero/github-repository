package com.tqx.design.strategy;

/**
 * @author Administrator
 * @version 1.0
 * @description: 策略模式上下文
 * @date 2026/3/21 21:28
 */
public class SuperMarketContext {

    private SuperMacketStrategy superMacketStrategy;

    public SuperMarketContext() {
    }

    public SuperMarketContext(SuperMacketStrategy superMacketStrategy) {
        this.superMacketStrategy = superMacketStrategy;
    }

    public SuperMarketContext setSuperMacketStrategy(SuperMacketStrategy superMacketStrategy) {
        this.superMacketStrategy = superMacketStrategy;
        return this;
    }

    public void getPrice() {
        superMacketStrategy.disCount();
    }
}
