package com.example.test.fina;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/25 11:56
 */
public class FinalChild extends FinalParent {

    //此处无法重写FinalParent 的final方法,但可以通过子类调用


    public static void main(String[] args) {
        FinalChild finalChild = new FinalChild();
        //此处调用了父类FinalParent的final方法
        finalChild.say();
        final List<Integer> name = new java.util.ArrayList<>(List.of(1, 2, 3, 4));
        name.set(1, 10);
        name.add(20);

//        String str1 ="str";
//        str1.intern();
//        String str1 ="str";
//        String str1 ="str";

        System.out.println("names== " + name);
    }
}
