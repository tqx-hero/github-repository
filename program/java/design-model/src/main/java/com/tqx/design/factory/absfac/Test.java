package com.tqx.design.factory.absfac;

/**
 * @author Administrator
 * @version 1.0
 * @description: 抽象工厂
 * @date 2026/3/21 21:18
 */
public class Test {

    public static void main(String[] args) {
        BenzFactory factory = new BenzFactory();
        factory.createCar().drive();
        factory.createTank().drive();
        factory.createMotoSycle().drive();
    }
}
