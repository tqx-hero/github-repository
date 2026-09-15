package com.tqx.design.factory.absfac;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 21:21
 */
public class BenzCar implements Car {
    @Override
    public void drive() {
        System.out.println("奔驰车在跑");
    }
}
