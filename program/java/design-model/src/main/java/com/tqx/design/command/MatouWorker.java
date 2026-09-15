package com.tqx.design.command;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/25 17:47
 */
public class MatouWorker implements Worker {
    @Override
    public void doWork() {
        System.out.println("搬沙包");
    }

    @Override
    public void rest() {
        System.out.println("吃午饭");
    }
}
