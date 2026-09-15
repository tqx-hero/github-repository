package com.tqx.thread.suanfa;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/16 21:43
 */
public class Suanfa {

    static int a = 10;
    static int b = 20;

    public static void main(String[] args) {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
        System.out.println("a=" + a + ",b=" + b);
    }
}

class Yihuo {

    static int[] a = {2, 2, 3, 4, 5, 6, 7, 7, 6, 5, 3};

    public static void main(String[] args) {
        int res = 0;
        for (int i = 0; i < a.length; i++) {
            res ^= a[i];
        }
        System.out.println(res);
    }

}
