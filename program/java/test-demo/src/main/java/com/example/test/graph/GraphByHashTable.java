package com.example.test.graph;

import java.util.Arrays;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 哈希表为结构生成的图
 * @date 2026/3/2 18:09
 */
public class GraphByHashTable<E, T> {

    Node<T>[] values;   //边集合，链表结构
    E[] pointVal;  //点的集合，数组，每个下标都存入边集合的链表，整体结构就是一个哈希表

    public GraphByHashTable(E[] pointVal) {
        this.pointVal = pointVal;
        values = new Node[pointVal.length];
    }

    @Override
    public String toString() {
        return "GraphByHashTable{" +
                "pointVal=" + Arrays.toString(pointVal) +
                ", values=" + Arrays.toString(values) +
                '}';
    }

    public GraphByHashTable() {
    }

    static class ListNode<E> {
        boolean isVisited = false;
        E node;

        public ListNode(E node) {
            this.node = node;
        }

        public ListNode(boolean isVisited, E node) {
            this.isVisited = isVisited;
            this.node = node;
        }
    }

    static class Node<T> {
        T value;
        Node<T> next;
        int size = 0;
        int index;  //临近点在点集合内的下标

        public Node(T value, int index) {
            this.value = value;
            this.index = index;
        }

        public Node() {
        }

        @Override
        public String toString() {
            return "Node{" +
                    "index=" + index +
                    ", value=" + value +
                    ", next=" + next +
                    ", size=" + size +
                    '}';
        }

        /**
         * 链表插入
         *
         * @param val
         */
        Node<T> push(T val, int idx) {
            if (size == 0) {
                value = val;
                index = idx;
            } else {
                //头插法插入链表
                Node<T> front = new Node<>(val, idx);
                front.next = next;
                this.next = front;
            }
            size++;
            return this;
        }

    }

    GraphByHashTable<E, T> setNode(int i, int j, T val) {
        return setNode(this.values[i], i, j, val);
    }

    GraphByHashTable<E, T> setNode(Node<T> node, int i, int j, T val) {
        if (Objects.isNull(pointVal))
            return null;
        if (i >= pointVal.length || j >= pointVal.length || i == j)
            return null;
        node = node == null ? new Node<>() : node;
        node = node.push(val, j);
        values[i] = node;
        return this;
    }

//    void list() {
//        GraphUserStack stack = new GraphUserStack();
//        for (int i = 0; i < pointVal.length; i++) {
//
//            //栈内存放new ListNode类型，逐步入栈，直到链表指向为空，开始回溯
//            E e = pointVal[i];
//            if(e){
//
//            }
//            new ListNode<>(true, e);
//            stack.push(e);
//            Node<T> node = values[i];
////            ListNode<E> node = new ListNode<>(true, values[i]);
//
//        }

    /// /        boolean isVisited = false;
//
//    }
    public static void main(String[] args) {
        GraphByHashTable<Character, Integer> graph = new GraphByHashTable<>(new Character[]{'A', 'B', 'C', 'D'});
        graph.setNode(0, 1, 200).
                setNode(0, 2, 300).
                setNode(0, 3, 320);
        System.out.println(graph);
    }

}
