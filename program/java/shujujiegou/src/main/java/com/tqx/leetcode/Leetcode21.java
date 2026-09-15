package com.tqx.leetcode;

import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * @author Administrator
 * @version 1.0
 * @description: 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
 * 输入：l1 = [1,2,4], l2 = [1,3,4]
 * 输出：[1,1,2,3,4,4]
 * 示例 2：
 * <p>
 * 输入：l1 = [], l2 = []
 * 输出：[]
 * 示例 3：
 * <p>
 * 输入：l1 = [], l2 = [0]
 * 输出：[0]
 * <p>
 * <p>
 * 提示：
 * <p>
 * 两个链表的节点数目范围是 [0, 50]
 * -100 <= Node.val <= 100
 * l1 和 l2 均按 非递减顺序 排列
 * @date 2026/4/2 5:38
 */
public class Leetcode21 {
    static class ListNode {
        int val;
        ListNode next;

        public ListNode(int val, ListNode next) {
            this.next = next;
            this.val = val;
        }

        public ListNode(int val) {
            this.val = val;
        }

        @Override
        public String toString() {
            return "ListNode{" +
                    "next=" + next +
                    ", val=" + val +
                    '}';
        }

        public ListNode() {
        }
    }

    //小顶堆方式
    static class Solution {

        public static ListNode mergeTwoLists(ListNode list1, ListNode list2) {
            PriorityQueue<ListNode> heap = new PriorityQueue<>(Comparator.comparingInt(o -> o.val));
            ListNode l1 = list1;
            ListNode l2 = list2;
            while (l1 != null) {
                ListNode next = l1.next;
                l1.next = null;
                heap.add(l1);
                l1 = next;
            }
            while (l2 != null) {
                ListNode next = l2.next;
                l2.next = null;
                heap.add(l2);
                l2 = next;
            }
            ListNode result = new ListNode();
            ListNode currentNode = result;
            while (!heap.isEmpty()) {
                currentNode.next = heap.poll();
                currentNode = currentNode.next;
            }
            return result.next;
        }
    }

    //直接连
    static class Solution1 {
        public static ListNode mergeTwoLists(ListNode list1, ListNode list2) {
            ListNode listNode = new ListNode(-1, null);
            ListNode pointNode = listNode;
            for (; list1 != null && list2 != null; ) {
                if (list1.val <= list2.val) {
                    pointNode.next = list1;
                    list1 = list1.next;
                } else {
                    pointNode.next = list2;
                    list2 = list2.next;
                }
                pointNode = pointNode.next;
            }
            pointNode.next = list1 == null ? list2 : list1;
            return listNode.next;
        }
    }


    public static ListNode createNode() {
        ListNode n1 = new ListNode(1);
        ListNode n2 = new ListNode(2);
        ListNode n3 = new ListNode(3);
        ListNode n4 = new ListNode(4);
        ListNode n5 = new ListNode(5);

        n1.next = n2;
        n2.next = n3;
        n3.next = n4;
        n4.next = n5;


        ListNode n6 = new ListNode(1);
        ListNode n7 = new ListNode(2);
        ListNode n8 = new ListNode(3);
        ListNode n9 = new ListNode(4);
        ListNode n10 = new ListNode(5);

        n6.next = n7;
        n7.next = n8;
        n8.next = n9;
        n9.next = n10;


        return n1;
    }

    public static void main(String[] args) {
//        System.out.println(createNode());
//        ListNode node = createNode();
//[-10,-10,-9,-4,1,6,6]
        //[-7]
        ListNode n1 = new ListNode(-10);
        ListNode n2 = new ListNode(-10);
        ListNode n3 = new ListNode(-9);
        ListNode n4 = new ListNode(-4);
        ListNode n5 = new ListNode(1);
        ListNode n0 = new ListNode(6);
        ListNode ns = new ListNode(6);

        n1.next = n2;
        n2.next = n3;
        n3.next = n4;
        n4.next = n5;
        n5.next = n0;
        n0.next = ns;


        ListNode n6 = new ListNode(-7);
//        ListNode n7 = new ListNode(2);
//        ListNode n8 = new ListNode(3);
//        ListNode n9 = new ListNode(4);
//        ListNode n10 = new ListNode(5);

//        n6.next = n7;
//        n7.next = n8;
//        n8.next = n9;
//        n9.next = n10;

        System.out.println(Solution1.mergeTwoLists(n1, n6));
    }
}
