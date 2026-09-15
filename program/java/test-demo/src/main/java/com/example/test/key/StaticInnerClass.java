package com.example.test.key;

/**
 * @author Administrator
 * @version 1.0
 * @description: 静态内部类
 * @date 2026/2/24 18:23
 */
public class StaticInnerClass {

    private static class innerClass {
        void get() {
            System.out.println("静态内部类.......");
        }
    }


    public static void main(String[] args) {
        StaticInnerClass.innerClass aClass = new StaticInnerClass.innerClass();
        aClass.get();

    }
}
