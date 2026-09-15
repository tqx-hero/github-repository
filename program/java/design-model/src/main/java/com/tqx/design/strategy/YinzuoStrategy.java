package com.tqx.design.strategy;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 21:32
 */
public class YinzuoStrategy implements SuperMacketStrategy {
    @Override
    public void disCount() {
        System.out.println("银座全场8折");
    }
}
