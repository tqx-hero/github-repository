package com.tqx.list.practice;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/8 12:44
 */
public class LinkedOperator {

    //链表的大小
    private int size;
    private LinkedNode head;
    //懒惰删除的链表节点数量
    private int deletedSize;
    //未被删除的节点数量
    private int unDeletedSize;

    public LinkedOperator() {
        this.size = 0;
        this.head = new LinkedNode();
    }

    public Iterator reverseLinked() {
        if (size == 0)
            return null;
        LinkedNode cur = head.next;
        while (cur != null && cur.val != null) {
            cur = cur.next;
        }
        return new ReverseIterator().setTail(cur.prev);
    }

//    @Override
//    public Iterator iterator() {
//        return new ReverseIterator();
//    }

    private static class ReverseIterator implements Iterator {
        private LinkedNode tail;

        public ReverseIterator setTail(LinkedNode tail) {
            this.tail = tail;
            return this;
        }

        @Override
        public boolean hasNext() {
            return tail != null && tail.val != null;
        }

        @Override
        public Object next() {
            Object val = tail.val;
            LinkedNode prev = tail.prev;
            tail.prev.next = null;
            tail.prev = null;
            tail = prev;
            return val;
        }
    }

    //惰性删除，节点批量删除
    public int deleteBatch() {
        if (deletedSize == 0)
            return 0;
        LinkedNode cur = head.next;
        int count = 0;
        while (cur != null && cur.val != null) {
            if (cur.deleted) {
                cur.prev.next = cur.next;
                cur.next.prev = cur.prev;
                cur.prev = null;
                cur.next = null;
                deletedSize--;
                unDeletedSize++;
                count++;
            }
        }
        return count;
    }

    private static class LinkedNode {
        Object val;
        LinkedNode next;
        LinkedNode prev;
        boolean deleted;  //设置该节点是否已经被标记删除

        public LinkedNode(Object val) {
            this.val = val;
        }

        @Override
        public String toString() {
            return "LinkedNode{" +
                    "next=" + next +
                    ", val=" + val +
                    '}';
        }

        public LinkedNode() {
        }

        public LinkedNode(LinkedNode next, Object val) {
            this.next = next;
            this.val = val;
        }

        public LinkedNode(LinkedNode next) {
            this.next = next;
        }
    }

    public int size() {
        return size;
    }

    //输出链表所有节点，不包括前哨头结点
    public List<Object> print() {
        if (size == 0)
            return null;
        ArrayList<Object> list = new ArrayList<>();
        LinkedNode cur = head.next;
        while (cur != null) {
            list.add(cur.val);
            cur = cur.next;
        }
        return list;
    }

    //查看是否包含数据
    public boolean contains(Object x) {
        if (size == 0)
            return false;
        boolean flag = false;
        LinkedNode cur = head.next;
        while (cur != null) {
            if (cur.val.equals(x))
                return true;
        }
        return flag;
    }

    public int addIfAbsent(Object x) {
        if (!contains(x)) {
            if (head == null)
                head = new LinkedNode();
            head.next = new LinkedNode(head.next, x);
            size++;
            return 1;
        }
        return 0;
    }

    public int removeIfAbsent(Object x) {
        if (size == 0)
            return 0;
        LinkedNode cur = head.next;
        LinkedNode prev = head;
        while (cur != null) {
            if (cur.val.equals(x)) {
                prev.next = cur.next;
                cur.next = null;
                size--;
                return 1;
            }
            cur = cur.next;
            prev = prev.next;
        }
        return 0;
    }

    public static void main(String[] args) {
        LinkedOperator operator = new LinkedOperator();
        int i = operator.addIfAbsent("str");
        System.out.println(operator.size());
        System.out.println(operator.contains("str"));
        System.out.println(operator.print());
        System.out.println(operator.removeIfAbsent("str"));
        System.out.println(operator.size());
    }
}

