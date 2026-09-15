package com.example.test.key;

/**
 * @author Administrator
 * @version 1.0
 * @description: 静态方法是类，不能重写，所以多态无效
 * Parent
 * Child==father
 * @date 2026/2/24 18:56
 */
public class Child extends Parent {
    public static void get() {
        System.out.println("Child");
    }

    @Override
    public void get(String str) {
        System.out.println("Child==" + str);
    }

    public static void main(String[] args) {
        Parent parent = new Child();
        parent.get();

        parent.get("father");
    }
}
