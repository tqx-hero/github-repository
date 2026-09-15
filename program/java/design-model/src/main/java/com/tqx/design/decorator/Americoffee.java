package com.tqx.design.decorator;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/13 21:26
 */
public class Americoffee implements Coffee {
    @Override
    public double cost() {
        return 10.00;
    }

    @Override
    public String desc() {
        return "美式咖啡";
    }
}
