package com.example.test.strings;

import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/25 12:25
 */
public class StringTest {

    public static void main(String[] args) {
        String a = "abc";
        String b = "abc";
        System.out.println(a == b);  //true,地址相同，都在常量池中

        String c = new String("abc"); //new String()实际上是在堆内新创建了一个对象，没有在常量池

        System.out.println(a == c);   //false, 一个在堆内，一个在常量池内，两者地址不一样，所以为false

        System.out.println(a.equals(c));  // true ,String 重写了equals()方法，使方法比较地址改成了比较值



    }
}
