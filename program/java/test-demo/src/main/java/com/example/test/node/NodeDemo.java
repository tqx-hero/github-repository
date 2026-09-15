package com.example.test.node;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个节点
 * @date 2026/2/26 13:56
 */
public class NodeDemo<E> {

    //节点存储的数据
    private E data;
    //节点存储的下节点地址
    private NodeDemo<E> next;

    public NodeDemo() {
    }

    public E getData() {
        return data;
    }

    public void setData(E data) {
        this.data = data;
    }

    public NodeDemo<E> getNext() {
        return next;
    }

    public void setNext(NodeDemo<E> next) {
        this.next = next;
    }

    @Override
    public String toString() {
        return "NodeDemo{" +
                "data=" + data +
                ", next=" + next +
                '}';
    }

    public NodeDemo(E data, NodeDemo<E> next) {
        this.data = data;
        this.next = next;
    }
}
