package com.example.test.model;

/**
 * @author Administrator
 * @version 1.0
 * @description: 静态内部类实现懒汉式单例:静态内部类在调用时才会加载,而且只加载一次
 * @date 2026/2/24 18:41
 */
public class LazySingleton {


    private static class NewInstance {

        static {
            System.out.println("静态内部类静态代码块加载");
        }

        private static final LazySingleton getInstance = new LazySingleton();
    }

    public LazySingleton() {
    }

    public static LazySingleton getInstance() {
        return NewInstance.getInstance;
    }

    public static void main(String[] args) {
        System.out.println("main方法启动.................");
        LazySingleton.getInstance();
        System.out.println("main方法结束");
    }


}
