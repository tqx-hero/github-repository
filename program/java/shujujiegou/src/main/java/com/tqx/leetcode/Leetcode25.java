package com.tqx.leetcode;

import java.util.ArrayDeque;
import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @description: k个一组翻转链表
 * 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
 * <p>
 * k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
 * <p>
 * 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
 * 输入：head = [1,2,3,4,5], k = 2
 * 输出：[2,1,4,3,5]
 * 输入：head = [1,2,3,4,5], k = 3
 * 输出：[3,2,1,4,5]
 * @date 2026/4/2 9:56
 */
public class Leetcode25 {

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

    //队列解决
    static class Solution {
        public static ListNode reverseKGroup(ListNode head, int k) {
            if (head == null || k == 1)
                return head;
            ArrayList<ListNode> nodeList = new ArrayList<>();
            ListNode currentNode = head;
            while (currentNode != null) {
                nodeList.add(currentNode);
                currentNode = currentNode.next;
            }
            int count = nodeList.size();
            int loopCount = count / k;
            if (loopCount == 0)
                return head;
            ArrayDeque<ListNode> queue = new ArrayDeque<>();
            for (int i = 1; i <= loopCount; i++) {
                //k个元素倒着放入队列
                int beginIndex = (i - 1) * k + k - 1;
                for (int j = 0; j < k; j++) {
                    queue.add(nodeList.get(beginIndex--));
                }
            }
            ListNode result = new ListNode(-1, null);
            ListNode subNode = result;
            while (!queue.isEmpty()) {
                ListNode node = queue.poll();
                node.next = null;
                subNode.next = node;
                subNode = subNode.next;
            }
            if (count % k != 0) {
                for (int i = loopCount * k; i < count; i++) {
                    subNode.next = nodeList.get(i);
                    subNode = subNode.next;
                }
            }
            return result.next;
        }
    }


    //针对k个元素翻转链表
    static class Solution1 {
        public static ListNode reverseKGroup(ListNode head, int k) {
            if (head == null || k == 1)
                return head;
            ListNode resultNode = new ListNode(-1);
            resultNode.next = head;
            ListNode current = head;
            ListNode prevNode = resultNode;
            while (current != null) {
                //
                ListNode curr = current;
                //查找第k个元素的尾结点
                ListNode prev = curr;
                int count = 0;
                for (int i = 0; i < k; i++) {
                    if (prev == null)
                        break;
                    ListNode next = prev.next;
                    count++;
                    prev = next;
                }
                //判断count有没有k个元素，没有则不需要翻转
                if (count != k)
                    break;
                //翻转这k个元素
                ListNode reversed = reverse(current, prev);
                current = prev;
                ListNode next = prevNode.next;
                prevNode.next = reversed;
                prevNode = next;
            }
            return resultNode.next;
        }
    }

    private static ListNode reverse(ListNode head, ListNode tail) {
        ListNode tl = tail;
        ListNode curr = head;
        ListNode prev = tl;
        while (curr != tl) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    public static void main(String[] args) {
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
//        n5.next = n6;
//        n6.next = n7;
//        n7.next = n8;
//        n8.next = n9;
//        n9.next = n10;
//        System.out.println(Leetcode25.reverse(n1, null));
        System.out.println(Solution1.reverseKGroup(n1, 2));
    }
}
