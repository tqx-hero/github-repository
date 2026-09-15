package com.example.test.stacks;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/26 14:40
 */
public class LinkedStackTest {

    public static void main(String[] args) {
        LinkedStackDemo<Object> demo = new LinkedStackDemo<>();
        demo.push(1);
        demo.push(2);
        demo.push(3);
        demo.push(4);
        System.out.println(demo);

        demo.pop();
        System.out.println("丢弃后==" + demo);
    }
}
