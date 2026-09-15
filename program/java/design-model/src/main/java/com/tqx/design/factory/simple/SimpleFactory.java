package com.tqx.design.factory.simple;

/**
 * @author Administrator
 * @version 1.0
 * @description: 简单工厂
 * @date 2026/3/21 21:03
 */
public class SimpleFactory {

    public Car createCar(String type) {
        switch (type) {
            case "BMW":
                return new BMW();
            case "Benz":
                return new Benz();
            default:
                return null;
        }
    }
}
