package com.example.test.entity;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个链表节点, 存放key，value以及下个节点的指针
 * @date 2026/2/27 9:51
 */
public class Entry {

    public Object key;
    public Object value;
    public Entry next;

    public Entry() {
    }

    @Override
    public String toString() {
        return "Entry{" +
                "key=" + key +
                ",value=" + value +
                ", next=" + next +
                '}';
    }

    public Entry(Object key, Object value) {
        this.key = key;
        this.value = value;
    }
}
