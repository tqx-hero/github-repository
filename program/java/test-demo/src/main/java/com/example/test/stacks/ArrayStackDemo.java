package com.example.test.stacks;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个数组栈
 * @date 2026/2/26 13:05
 */
public class ArrayStackDemo {

    private int idx = -1;

    private Object[] arr;

    @Override
    public String toString() {
        return "ArrayStackDemo{" +
                "idx=" + idx +
                ", arr=" + Arrays.toString(arr) +
                ", size=" + size +
                '}';
    }

    private int size = 10;

    private static final int MAX_COMPOSY_PARAM = 2;

    public ArrayStackDemo(Object[] arr) {
        this.arr = arr;
    }

    public ArrayStackDemo(int size) {
        this.size = size;
        arr = new Object[size];
    }

    public ArrayStackDemo() {
        this.arr = new Object[size];
    }

    public boolean isEmpty() {
        return idx == -1;
    }


    public boolean isFull() {
        return idx == size - 1;
    }

    public void push(Object obj) {
        if (isFull()) {
            System.out.println("需要扩容");
            resize();
        }
        arr[++idx] = obj;
    }

    public boolean resize() {
        int newSize = size * MAX_COMPOSY_PARAM;
        Object[] newObj = new Object[newSize];
        System.arraycopy(arr, 0, newObj, 0, size);
        arr = newObj;
        size = newSize;
        return true;
    }

    public Object pop() {
        if (isEmpty())
            return null;
        Object obj = arr[idx];
        arr[idx--] = null;
        return obj;
    }

    public Object peek() {
        if (isEmpty())
            return null;
        return arr[idx];
    }
}
