package com.tqx.design.singleton;

public enum SingletonEnum {
    INSTANCE;
}

class InnerClasss {
    public static void main(String[] args) {
        SingletonEnum instance = SingletonEnum.INSTANCE;
        SingletonEnum instance1 = SingletonEnum.INSTANCE;
        System.out.println(instance1 == instance);
    }
}
