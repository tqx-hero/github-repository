package com.tqx.design.decorator;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义装饰器规范
 * @date 2026/4/13 21:26
 */
public abstract class Decorator implements Coffee {

    protected Coffee coffee;

    public Decorator(Coffee coffee) {
        this.coffee = coffee;
    }

    @Override
    public double cost() {
        return coffee.cost();
    }

    @Override
    public String desc() {
        return coffee.desc();
    }
}
