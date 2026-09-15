package com.tqx.design.decorator;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/13 21:30
 */
public class MilkDecorator extends Decorator {

    public MilkDecorator(Coffee coffee) {
        super(coffee);
    }

    @Override
    public double cost() {
        return coffee.cost() + 3;
    }

    @Override
    public String desc() {
        return coffee.desc() + ",加奶3块";
    }
}
