package com.tqx.design.factory_strategy;


/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 21:32
 */
@SuperMarket
public class YinzuoStrategy implements SuperMartStrategy {
    @Override
    public void disCount() {
        System.out.println("银座全场8折");
    }
}
