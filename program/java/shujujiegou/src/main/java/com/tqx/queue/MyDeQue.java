package com.tqx.queue;

/**
 * @author Administrator
 * @version 1.0
 * @description: 双端队列, 从数组中间往两边加
 * @date 2026/4/8 17:16
 */
public class MyDeQue {

    private Object[] arr;
    private int size;
    private int count;
    private int front;
    private int rear;

    public MyDeQue(int size) {
        this.size = size + 1;
        this.arr = new Object[this.size];
        arr[0] = Integer.MAX_VALUE;
        int index = this.size / 2;
        this.front = index;
        this.rear = index;
        this.count = 0;
    }

    public void inject(Object o) {
        if (count >= size)
            throw new IndexOutOfBoundsException("队列已满");
        arr[rear++] = o;
        count++;
    }

    public void push(Object x) {
        if (count >= size)
            throw new IndexOutOfBoundsException("队列已满");
        arr[--front] = x;
        count++;
    }

    public Object pop() {
        if (count == 0)
            throw new IndexOutOfBoundsException("队列已空");
        Object o = arr[front++];
        count--;
        return o;
    }

    public Object eject() {
        if (count == 0)
            throw new IndexOutOfBoundsException("队列已空");
        Object o = arr[--rear];
        count--;
        return o;
    }

    public static void main(String[] args) {
        MyDeQue deQue = new MyDeQue(10);
        deQue.push(10);
        deQue.push(20);
        deQue.inject(30);
        System.out.println(deQue.pop());
        System.out.println(deQue.eject());
    }

}
