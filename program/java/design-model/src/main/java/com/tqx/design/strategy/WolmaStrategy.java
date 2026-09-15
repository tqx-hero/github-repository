package com.tqx.design.strategy;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 21:31
 */
public class WolmaStrategy implements SuperMacketStrategy {
    @Override
    public void disCount() {
        System.out.println("沃尔玛全场9折");
    }
}
