package com.tqx.design.factory.method;

/**
 * @author Administrator
 * @version 1.0
 * @description: 工厂方法
 * @date 2026/3/21 21:14
 */
public class Test {
    public static void main(String[] args) {
        new BenzFactory().createCar().drive();
        new BMWFactory().createCar().drive();
    }
}
