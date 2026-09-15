package com.example.test.stacks;

import com.example.test.node.NodeDemo;

/**
 * @author Administrator
 * @version 1.0
 * @description: 头插法实现栈
 * @date 2026/2/26 13:48
 */
public class LinkedStackDemo<E> {

    //节点个数
    private int count = 0;

    //头结点
    private NodeDemo<E> head;

    @Override
    public String toString() {
        return "LinkedStackDemo{" +
                "count=" + count +
                ", head=" + head +
                '}';
    }

    public LinkedStackDemo(int count, NodeDemo<E> head) {
        this.count = count;
        this.head = head;
    }

    public LinkedStackDemo() {
    }

    /**
     * 链表头插法-栈
     */
    public void push(E data) {
        //新建节点，将数据存储
        NodeDemo<E> objectNodeDemo = new NodeDemo<>(data, null);
        if (count != 0) {
            objectNodeDemo.setNext(head);
        }
        head = objectNodeDemo;
        count++;
    }

    /**
     * 删除头部节点
     *
     * @return
     */
    public E pop() {
        if (count == 0) return null;
        E data = head.getData();
        //获取头部第二个节点
        head = head.getNext();
        count--;
        return data;
    }


}
