package com.example.test.key;

/**
 * @author Administrator
 * @version 1.0
 * 执行顺序：1、静态代码块，类加载时执行，仅执行一次，2、执行main方法，按顺序执行；3、创建对象时，先执行构造代码块；4、执行构造方法；5、顺序执行
 * 静态代码块加载。。。。。。。。
 * 构造方法创建之前.......................
 * 构造代码块加载.........................
 * 构造方法创建.........................
 * main方法执行中......................
 * @date 2026/2/24 18:13
 */
public class StaticTest {

    static {
        System.out.println("静态代码块加载。。。。。。。。");
    }

    {
        System.out.println("构造代码块加载.........................");
    }

    StaticTest() {
        System.out.println("构造方法创建.........................");
    }

    public static void main(String[] args) {
        System.out.println("构造方法创建之前.......................");
        new StaticTest();
        new StaticTest();
        System.out.println("main方法执行中......................");
    }


}
