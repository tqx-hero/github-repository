package com.example.test.stacks;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/26 13:26
 */
public class ArrayStackTest {

    public static void main(String[] args) {
        ArrayStackDemo arrayStackDemo = new ArrayStackDemo(5);

        arrayStackDemo.push("1");
        arrayStackDemo.push("2");
        arrayStackDemo.push("3");
        arrayStackDemo.push("4");
        arrayStackDemo.push("5");
        arrayStackDemo.push("6");
        System.out.println("arrayStackDemo== " + arrayStackDemo);

        Object pop = arrayStackDemo.pop();
        System.out.println("pop==" + pop);

        System.out.println("arrayStackDemo== " + arrayStackDemo);

    }
}
