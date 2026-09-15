package com.tqx.list.practice;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 栈与队列的练习
 * @date 2026/4/8 9:25
 */
public class StackAndQueue {

    private static class Node {
        int val;
        Node next;

        public Node(Node next, int val) {
            this.next = next;
            this.val = val;
        }

        @Override
        public String toString() {
            return "Node{" +
                    "next=" + next +
                    ", val=" + val +
                    '}';
        }
    }

    static class DoubleNode {
        Integer val;
        DoubleNode prev;
        DoubleNode next;

        @Override
        public String toString() {
            return "DoubleNode{" +
                    "next=" + next +
                    ", val=" + val +
//                    ", prev=" + prev +
                    '}';
        }

        public DoubleNode(DoubleNode next, DoubleNode prev, Integer val) {
            this.next = next;
            this.prev = prev;
            this.val = val;
        }
    }

    //3.1 ArrayList查找是O(p.size) ,LinkedList的话，需要O(p.size+l.size)，查找需要指针遍历过去
    public static void printLots(List<String> l, List<Integer> p) {
        for (Integer i : p) {
            System.out.println(l.get(i));
        }
    }

    //单链表的两个节点交换
    public static Node changeNode(int a, int b) {
        Node tail = new Node(null, Integer.MAX_VALUE);
        Node na = new Node(tail, a);
        Node nb = new Node(na, b);
        Node head = new Node(nb, Integer.MIN_VALUE);
        //交换链表相邻的两个节点
        nb.next = na.next;
        na.next = nb;
        head.next = na;
        return head.next;
    }

    //交换双向链表的两个相邻节点
    public static DoubleNode changeDoubleNode(Integer a, Integer b) {
        //前哨节点，头尾
        DoubleNode head = new DoubleNode(null, null, Integer.MAX_VALUE);
        DoubleNode tail = new DoubleNode(null, null, Integer.MAX_VALUE);

        DoubleNode adn = new DoubleNode(null, head, a);
        DoubleNode bdn = new DoubleNode(tail, adn, b);
        head.next = adn;
        adn.next = tail.prev = bdn;
        // a ->b
        DoubleNode bnext = bdn.next;
        DoubleNode aprev = adn.prev;
        bdn.next = adn;
        adn.next = bnext;
        adn.prev = bdn;
        bdn.prev = aprev;
        aprev.next = bdn;
        return head;
    }


    //L1与L2的交集
    //前提是两个有序集合
    public static List<Integer> getCross(List<Integer> l1, List<Integer> l2) {
        if (l1 == null || l2 == null || l1.isEmpty() || l2.isEmpty())
            return null;
        int index1 = 0, index2 = 0;
        ArrayList<Integer> result = new ArrayList<>();
        while (index1 < l1.size() && index2 < l2.size()) {
            int val1 = l1.get(index1);
            int val2 = l2.get(index2);
            if (val1 == val2) {
                result.add(val1);
                index1++;
                index2++;
            }
            // 数值小的那个集合的指针前移
            //如果l1大于l2，index2前移
            //否则index1前移
            else if (val1 > val2)
                index2++;
            else
                index1++;
        }
        return result;
    }

    //L1与L2的并集
    //前提是两个有序集合
    public static List<Integer> getUnion(List<Integer> l1, List<Integer> l2) {
        if (l1 == null && l2 == null)
            return null;
        if (l1.isEmpty())
            return l2;
        else if (l2.isEmpty())
            return l1;
        ArrayList<Integer> result = new ArrayList<>();
        int index1 = 0, index2 = 0;
        int s1 = l1.size();
        int s2 = l2.size();
        while (index1 < s1 && index2 < s2) {
            int val1 = l1.get(index1);
            int val2 = l2.get(index2);
            int added = val1;
            if (val1 == val2) {
                index2++;
                index1++;
            } else if (val1 < val2)
                index1++;
            else {
                added = val2;
                index2++;
            }
            result.add(added);
        }
        while (index1 < s1)
            result.add(l1.get(index1++));
        while (index2 < s2)
            result.add(l2.get(index2++));
        return result;
    }

    //解决Josephus问题，m为传递次数
    //n为初始游戏的人数，序号从1开始
    //返回人的序号
    public static int resolveJosephus(int m, int n) {
        if (n == 1)
            return n;
        //设置初始链表数量，当前链表头节点指针
        int size = n;
        //构建链表环
        Node node = new Node(null, n);
        Node head = node;
        for (int i = n - 1; i > 0; i--)
            head = new Node(head, i);
        node.next = head;
        //当前指向的节点指针,与该节点的前驱节点
        Node cur = head;
        Node prev = node;
        while (size > 1) {
            //  次数/人数是否被除尽
            //当被除尽时，不用循环，当前指针的节点直接出链
            //同时指针指向next,n-1
            int remain = m % size;
            //除不尽，则按照余数进行传递
            //找到要删除的节点
            for (int r = 1; r <= remain; r++) {
                cur = cur.next;
                prev = prev.next;
            }
            cur = prev.next = cur.next;
            size--;
        }
        return cur.val;
    }

    public static void main(String[] args) {
        //调换链表的2个相邻节点
//        System.out.println(StackAndQueue.changeNode(2, 1));
//        System.out.println(StackAndQueue.changeDoubleNode(1, 2));

        //找出2个集合L1与L2的交集（两个集合都是有序集合）
//        System.out.println(StackAndQueue.getCross(Arrays.asList(10, 20, 30), Arrays.asList(20, 30, 40)));
        //找出2个集合L1与L2的并集（两个集合都是有序集合）
//        System.out.println(StackAndQueue.getUnion(Arrays.asList(10, 20, 30), Arrays.asList(20, 30, 40)));
        System.out.println(StackAndQueue.resolveJosephus(10, 5));
    }


}
