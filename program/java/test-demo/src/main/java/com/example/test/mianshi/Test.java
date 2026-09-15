package com.example.test.mianshi;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/3 20:07
 */
public class Test {

    public static void main(String[] args) {
        Singleton instance = Singleton.getInstance();
        Singleton instance1 = Singleton.getInstance();
        System.out.println(instance == instance1);
    }
}
