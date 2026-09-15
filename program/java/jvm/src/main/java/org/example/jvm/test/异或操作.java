package org.example.jvm.test;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/5 11:10
 */
public class 异或操作 {
    public static void main(String[] args) {
        int a = 10;
        int b = 20;
        a = a ^ b;
        b = a ^ b;
        a = b ^ a;

        System.out.println("a==" + a + ",b==" + b);
    }
}
