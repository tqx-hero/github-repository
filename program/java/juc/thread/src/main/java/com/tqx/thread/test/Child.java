package com.tqx.thread.test;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 16:30
 */
public class Child extends Parent {

    @Override
    public void getName() {
        System.out.println("子类");
    }

    public static void main(String[] args) {
        Parent parent = new Child();
        parent.get();
    }
}
