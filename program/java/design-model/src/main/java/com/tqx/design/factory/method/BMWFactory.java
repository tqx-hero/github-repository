package com.tqx.design.factory.method;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 21:14
 */
public class BMWFactory implements CarFactory {
    @Override
    public Car createCar() {
        return new BMW();
    }
}
