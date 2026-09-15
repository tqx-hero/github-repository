package com.tqx.design.strategy;

/**
 * @author Administrator
 * @version 1.0
 * @description: 策略模式
 * @date 2026/3/21 21:32
 */
public class Test {

    public static void main(String[] args) {
        //1、构造器注入方式
        new SuperMarketContext(new WolmaStrategy()).getPrice();
        new SuperMarketContext(new YinzuoStrategy()).getPrice();

        //2、setter注入方式
        SuperMarketContext context = new SuperMarketContext();
        context.setSuperMacketStrategy(new WolmaStrategy()).getPrice();
        context.setSuperMacketStrategy(new YinzuoStrategy()).getPrice();
    }
}
