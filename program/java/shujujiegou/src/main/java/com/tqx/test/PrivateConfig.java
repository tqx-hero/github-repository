package com.tqx.test;

/**
 * @author Administrator
 * @version 1.0
 * @description: 方法/函数属于类，变量属于对象，所以同一类的方法可以访问这个类对象的所有变量，包括private
 * @date 2026/7/3 11:07
 */
public class PrivateConfig {

    private int num;
    int sum;

    void set(int n) {
        this.num = n;
    }

    int get(PrivateConfig config) {
        return config.num;
    }
}

class Tes {

    public static void main(String[] args) {
        PrivateConfig config = new PrivateConfig();
        config.set(10);
        PrivateConfig config2 = new PrivateConfig();
        System.out.println(config2.get(config));
    }
}
