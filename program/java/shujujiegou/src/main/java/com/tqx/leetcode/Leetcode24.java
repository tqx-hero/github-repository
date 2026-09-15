package com.tqx.leetcode;

import java.util.ArrayDeque;

/**
 * @author Administrator
 * @version 1.0
 * @description: 两两交换链表中的节点
 * 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。
 * 输入：head = [1,2,3,4]
 * 输出：[2,1,4,3]
 * 示例 2：
 * <p>
 * 输入：head = []
 * 输出：[]
 * 示例 3：
 * <p>
 * 输入：head = [1]
 * 输出：[1]
 * @date 2026/4/2 9:02
 */
public class Leetcode24 {

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

    static class Solution {
        public static ListNode swapPairs(ListNode head) {
            if (head == null || head.next == null)
                return head;
            ArrayDeque<ListNode> queue = new ArrayDeque<>();

            while (head != null) {
                queue.add(head);
                head = head.next;
            }
            ListNode resultNode = new ListNode(-1);
            ListNode currentNode = resultNode;
            while (!queue.isEmpty() && queue.size() >= 2) {
                ListNode n1 = queue.poll();
                ListNode n2 = queue.poll();
                n1.next = n2.next;
                n2.next = n1;
                currentNode.next = n2;
                currentNode = currentNode.next.next;
            }
            if (!queue.isEmpty()) {
                currentNode.next = queue.poll();
            }
            return resultNode.next;
        }
    }

    public static void main(String[] args) {
        ListNode n1 = new ListNode(1);
        ListNode n2 = new ListNode(2);
        ListNode n3 = new ListNode(3);
        ListNode n4 = new ListNode(4);
        ListNode n5 = new ListNode(5);

//        n1.next = n2;
//        n2.next = n3;
//        n3.next = n4;
//        n4.next = n5;


        ListNode n6 = new ListNode(1);
        ListNode n7 = new ListNode(2);
        ListNode n8 = new ListNode(3);
        ListNode n9 = new ListNode(4);
        ListNode n10 = new ListNode(5);

        n6.next = n7;
        n7.next = n8;
        n8.next = n9;
        n9.next = n10;
        System.out.println(Solution.swapPairs(n1));
    }
}
