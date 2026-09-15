package com.example.test.que;

import com.example.test.node.NodeDemo;

/**
 * @author Administrator
 * @version 1.0
 * @description: 链表队列
 * @date 2026/2/26 17:59
 */
public class LinkedQueueDemo<E> {

    private NodeDemo<E> front;
    private NodeDemo<E> rear;


    private int size = 0;

    public LinkedQueueDemo() {
    }

    public NodeDemo<E> getFront() {
        return front;
    }

    @Override
    public String toString() {
        return "LinkedQueueDemo{" +
                "front=" + front +
                ", rear=" + rear +
                ", size=" + size +
                '}';
    }

    public void setFront(NodeDemo<E> front) {
        this.front = front;
    }

    public NodeDemo<E> getRear() {
        return rear;
    }

    public void setRear(NodeDemo<E> rear) {
        this.rear = rear;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    /**
     * 入列:尾插
     *
     * @param e
     */
    public void push(E e) {
        NodeDemo<E> nodeDemo = new NodeDemo<>(e, null);
        if (front == null) {
            front = nodeDemo;
            rear = front;
        } else {
            rear.setNext(nodeDemo);
            rear = nodeDemo;
        }
        size++;
    }

    /**
     * 删除头部记录
     *
     * @return
     */
    public void pop() {
        if (front == null) return;

        if (size == 1) {
            front = null;
            rear = null;
        } else {
            NodeDemo<E> frontNext = front.getNext();
            front.setNext(null);
            front = frontNext;
        }
        size--;
    }

}
