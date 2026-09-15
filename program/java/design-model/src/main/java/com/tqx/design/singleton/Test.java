package com.tqx.design.singleton;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 22:54
 */
public class Test {

    public static void main(String[] args) throws NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
//        Hungry hungry = Hungry.getInstance();
//        Hungry hungry1 = Hungry.getInstance();
//        System.out.println(hungry1 == hungry);

//        LazyNoSync instance = LazyNoSync.getInstance();
//        LazyNoSync instanc1 = LazyNoSync.getInstance();
//        System.out.println(instance == instanc1);

//        LazySync instance = LazySync.getInstance();
//        LazySync instanc1e = LazySync.getInstance();
//        System.out.println(instance == instanc1e);

        InnerClass instance = InnerClass.getInstance();

        Constructor<InnerClass> constructor = InnerClass.class.getDeclaredConstructor();
        constructor.setAccessible(true);
        InnerClass innerClass = constructor.newInstance();
        System.out.println(instance == innerClass);
    }
}
