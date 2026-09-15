package com.tqx.demo;


/**
 * @author Administrator
 * @version 1.0
 * @description: 用栈来实现队列
 * @date 2026/3/30 7:44
 */
public class SimpleQueue {

    private static final int DEFAULT_SIZE = 1 << 6;
    private final SimpleStack inStack;
    private final SimpleStack outStack;
    private final int capacity;
    private volatile int totalCount;
    private static final Object LK = new Object();

    public SimpleQueue() {
        this(DEFAULT_SIZE);
    }

    public SimpleQueue(int capacity) {
        if (capacity <= 0)
            throw new IllegalArgumentException("容量输入需要大于0!");
        this.capacity = capacity;
        this.inStack = new SimpleStack(capacity);
        this.outStack = new SimpleStack(capacity);
    }

    private void transferData() {
        if (outStack.isEmpty() && !inStack.isEmpty()) {
            while (!inStack.isEmpty()) {
                outStack.push(inStack.pop());
            }
        }
    }

    public int size() {
        synchronized (LK) {
            return totalCount;
        }
    }

    public Object peek() {
        synchronized (LK) {
            transferData();
            return outStack.isEmpty() ? null : outStack.peek();
        }
    }

    public Object pop() {
        synchronized (LK) {
            transferData();
            if (outStack.isEmpty())
                return null;
            totalCount--;
            return outStack.pop();
        }
    }

    public void push(Object x) {
        if (x == null)
            throw new NullPointerException("传入数据不能为null");
        synchronized (LK) {
            if (totalCount >= capacity)
                throw new IllegalStateException("队列已满!");
            inStack.push(x);
            totalCount++;
        }
    }

    public boolean isEmpty() {
        synchronized (LK) {
            return totalCount == 0;
        }
    }

    private static class SimpleStack {
        private final Object[] valArr;
        private int headIndex;

        public SimpleStack(int capacity) {
            valArr = new Object[capacity];
            this.headIndex = -1;
        }

        private void push(Object x) {
            valArr[++headIndex] = x;
        }

        private Object pop() {
            return valArr[headIndex--];
        }

        private boolean isEmpty() {
            return headIndex == -1;
        }

        private Object peek() {
            return valArr[headIndex];
        }
    }

    public static void main(String[] args) {
        SimpleQueue queue = new SimpleQueue();
        int count = queue.totalCount;
        System.out.println(count);
        queue.push(10);
        queue.push(20);
        System.out.println(queue.pop());
        System.out.println(queue.peek());
        System.out.println(queue.isEmpty());
    }

}
