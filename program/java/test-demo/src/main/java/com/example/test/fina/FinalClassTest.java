package com.example.test.fina;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/25 11:38
 */
public class FinalClassTest {

    public final List<Integer> list = List.of(1, 2, 3, 4);

    public FinalClassTest() {
//        list = new ArrayList<>();
    }

    public static void main(String[] args) {

        FinalClassTest finalClassTest = new FinalClassTest();
        finalClassTest.list.add(5);
        //已定义并赋值的变量不允许再次修改
//        finalClassTest.list = new ArrayList<>();

    }
}