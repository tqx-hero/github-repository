package com.example.test.btree;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/3 19:03
 */
public class Arges<T> {

     void add(String str, T... agre) {
        for (int i = 0; i < agre.length; i++) {
            System.out.println(agre[i]);
        }
    }

    public static void main(String[] args) {
        Arges<Integer> arges = new Arges<>();
        arges.add("aaa",1, 2);
    }
}
