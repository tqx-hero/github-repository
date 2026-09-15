package com.example.test.link;

import com.example.test.node.NodeDemo;

/**
 * @author Administrator
 * @version 1.0
 * @description: 手搓链表
 * @date 2026/2/26 15:03
 */
public class LinkedDemo<E> {

    private NodeDemo<E> head;

    private int count = 0;


    public LinkedDemo(NodeDemo<E> head, int count) {
        this.head = head;
        this.count = count;
    }

    @Override
    public String toString() {
        return "LinkedDemo{" +
                "head=" + head +
                ", count=" + count +
                '}';
    }

    public LinkedDemo() {
    }

    /**
     * 头插法
     *
     * @param data
     */
    public void pushHead(E data) {
        //新建节点，将数据存储
        NodeDemo<E> objectNodeDemo = new NodeDemo<>(data, null);
        if (count != 0) {
            objectNodeDemo.setNext(head);
        }
        head = objectNodeDemo;
        count++;
    }

    /**
     * 尾插法
     *
     * @param data
     */
    public void pushNext(E data) {
        //新建节点，将数据存储
        NodeDemo<E> objectNodeDemo = new NodeDemo<>(data, null);
        if (count == 0) {
            head = objectNodeDemo;
        } else {
            NodeDemo<E> demo = head;
            while (demo.getNext() != null) {
                demo = demo.getNext();
            }
            demo.setNext(objectNodeDemo);
        }
        count++;

    }

    public E getHead() {
        return count == 0 ? null : head.getData();
    }

    public E getNext() {
        if (count == 0) return null;
        NodeDemo<E> demo = head;
        while (demo.getNext() != null) {
            demo = demo.getNext();
        }
        return demo.getData();
    }


    /**
     * 删除中间索引为index的元素
     *
     * @param index 索引
     */
    public void remove(int index) {
        if (index > count - 1) throw new IndexOutOfBoundsException();
        NodeDemo<E> demo = head;
        //去头
        if (index == 0) {
            if (count == 1) {
                head = null;
            } else {
                head = head.getNext();
            }
            count--;
            return;
        }
        for (int i = 0; i <= index; i++) {
            if (i == index - 1) {
                NodeDemo<E> del = demo.getNext();
                if (del != null) {
                    demo.setNext(del.getNext());
                    del.setNext(null);
                    del.setData(null);
                } else {
                    demo.setNext(null);
                }
                count--;
                break;
            } else {
                demo = demo.getNext();
            }
        }
    }

    public static void main(String[] args) {
        LinkedDemo<Object> obj = new LinkedDemo<>();
        obj.pushHead("a");
        obj.pushNext("c");
        obj.pushNext("b");
        System.out.println(obj);
        System.out.println("head==" + obj.getHead());
        System.out.println("next==" + obj.getNext());


        obj.remove(2);
        System.out.println("head==" + obj);

    }
}
