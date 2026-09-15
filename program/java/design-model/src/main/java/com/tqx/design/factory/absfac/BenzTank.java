package com.tqx.design.factory.absfac;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 21:22
 */
public class BenzTank implements Tank {
    @Override
    public void drive() {
        System.out.println("奔驰坦克在跑");
    }
}
