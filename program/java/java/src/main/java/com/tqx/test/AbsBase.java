package com.tqx.test;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/15 19:02
 */
public abstract class AbsBase {

    abstract void print();
}

interface InterA {
    default void print() {
        System.out.println("接口");
    }
}

class Child extends AbsBase implements InterA {

    @Override
    public void print() {
        System.out.println("child");
    }
}

//class  TEst{
//    public static void main(String[] args) {
//        List< ? extends Number> l = new ArrayList<Integer>();
//        l.add(new Integer(10));
//
//        List<? super  Integer> l1 =new ArrayList<Number>();
//        l1.add(20);
//    }
//}


