package com.tqx.design.factory_strategy;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 21:39
 */
public class SuperMarketContext {

    private SuperMartStrategy superMartStrategy;

    public SuperMarketContext setSuperMartStrategy(SuperMartStrategy superMartStrategy) {
        this.superMartStrategy = superMartStrategy;
        return this;
    }

    void getPrice() {
        superMartStrategy.disCount();
    }
}
