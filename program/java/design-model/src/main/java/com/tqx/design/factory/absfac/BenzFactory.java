package com.tqx.design.factory.absfac;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 21:20
 */
public class BenzFactory implements MachineFactory {

    @Override
    public Car createCar() {
        return new BenzCar();
    }

    @Override
    public MotoSycle createMotoSycle() {
        return new BenzMotoSycle();
    }

    @Override
    public Tank createTank() {
        return new BenzTank();
    }
}
