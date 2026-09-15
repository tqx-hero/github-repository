package com.tqx.design.factory.simple;

/**
 * @author Administrator
 * @version 1.0
 * @description: 简单工厂
 * @date 2026/3/21 21:10
 */
public class Test {

    public static void main(String[] args) {
        new SimpleFactory().createCar("Benz").drive();
    }
}
