package com.tqx.think;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/24 8:20
 */
public class TS<T> {

    T item;

    public TS(T item) {
        this.item = item;
    }

    //静态方法的泛型方法
    public static <T> T get(T data) {
        return data;
    }

    //使用多个类型参数的泛型方法
    public static <K, V> Tru<K, V> gets(K a, V c) {
        return new Tru<>(a, c);
    }
}

//继承类的泛型
class TSChild<T, E> extends TS<T> {

    private E nums;

    public TSChild(T item, E nums) {
        super(item);
        this.nums = nums;
    }
}


