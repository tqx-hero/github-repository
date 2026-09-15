package com.tqx.design.decorator;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/13 21:28
 */
public class SugurDecorator extends Decorator {
    //调用父类构造器注入对象的接口规范
    public SugurDecorator(Coffee coffee) {
        super(coffee);
    }

    @Override
    public String desc() {
        return coffee.desc() + ",加糖2块";
    }

    @Override
    public double cost() {
        return coffee.cost() + 2;
    }
}
