package com.tqx.design.factory_strategy;


import com.tqx.design.factory_strategy.ann.AOP;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 21:31
 */
@AOP
public class WolmaStrategy implements SuperMartStrategy {
    @Override
    public void disCount() {
        System.out.println("沃尔玛全场9折");
    }
}
