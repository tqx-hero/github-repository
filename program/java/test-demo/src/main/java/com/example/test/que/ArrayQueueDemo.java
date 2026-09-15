package com.example.test.que;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个数组构成的队列
 * @date 2026/2/26 10:59
 */
public class ArrayQueueDemo {

    private int front = 0;
    private int rear = 0;

    private int size = 10;

    private Object[] arr;

    private static final int MAX_COMPOTY_PARAM = 2;

    @Override
    public String toString() {
        return "QueueDemo{" +
                "arr=" + Arrays.toString(arr) +
                '}';
    }

    public ArrayQueueDemo(int size) {
        this.size = size;
        arr = new Object[size];
    }

    public int getFront() {
        return front;
    }

    public void setFront(int front) {
        this.front = front;
    }

    public int getRear() {
        return rear;
    }

    public void setRear(int rear) {
        this.rear = rear;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public Object[] getArr() {
        return arr;
    }

    public void setArr(Object[] arr) {
        this.arr = arr;
    }

    public ArrayQueueDemo() {
        arr = new Object[size];
    }

    public boolean isEmpty() {
        return front == rear;
    }

    public boolean isFull() {
        return front == (rear + 1) % size;
    }

    /**
     * 添加
     *
     * @param e
     * @return
     */
    public boolean add(Object e) {
        if (isFull()) {
            System.out.println("队列已满....");
            bigger();
            arr[rear] = e;
            rear = (rear + 1) % size;
            return true;
        }
        arr[rear] = e;
        rear = (rear + 1) % size;
        return true;
    }

    /**
     * 删除
     *
     * @return
     */
    public Object del() {
        if (isEmpty())
            return false;
        Object o = arr[front];
        front = (front + 1) % size;
        return o;

    }

    /**
     * 扩容
     *
     * @return
     */
    public boolean bigger() {
//        int resize = size * MAX_COMPOTY_PARAM;
        int resize = size + (size >> 1);
        Object[] newObj = new Object[resize];
        System.arraycopy(arr, 0, newObj, 0, size);
        arr = newObj;
        size = resize;
        return true;
    }


    static void add(){

    }

    /**
     * 查询头部元素
     *
     * @return
     */
    public Object peek() {
        return isEmpty() ? null : arr[front];
    }

}
