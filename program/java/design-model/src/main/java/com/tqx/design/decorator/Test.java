package com.tqx.design.decorator;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/13 21:31
 */
public class Test {

    public static void main(String[] args) {
        Coffee c = new Americoffee();
        c = new MilkDecorator(c);
        System.out.println(c.desc() + ",当前价格:" + c.cost());
        c = new SugurDecorator(c);
        System.out.println(c.desc() + ",当前价格:" + c.cost());
    }
}
