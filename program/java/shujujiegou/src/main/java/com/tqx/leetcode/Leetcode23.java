package com.tqx.leetcode;

import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * @author Administrator
 * @version 1.0
 * @description: 合并 K 个升序链表
 * 给你一个链表数组，每个链表都已经按升序排列。
 * <p>
 * 请你将所有链表合并到一个升序链表中，返回合并后的链表。
 * <p>
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * 输入：lists = [[1,4,5],[1,3,4],[2,6]]
 * 输出：[1,1,2,3,4,4,5,6]
 * 解释：链表数组如下：
 * [
 * 1->4->5,
 * 1->3->4,
 * 2->6
 * ]
 * 将它们合并到一个有序链表中得到。
 * 1->1->2->3->4->4->5->6
 * 示例 2：
 * <p>
 * 输入：lists = []
 * 输出：[]
 * 示例 3：
 * <p>
 * 输入：lists = [[]]
 * 输出：[]
 * <p>
 * <p>
 * 提示：
 * <p>
 * k == lists.length
 * 0 <= k <= 10^4
 * 0 <= lists[i].length <= 500
 * -10^4 <= lists[i][j] <= 10^4
 * lists[i] 按 升序 排列
 * lists[i].length 的总和不超过 10^4
 * @date 2026/4/2 6:51
 */
public class Leetcode23 {
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

    //直接破解
    static class Solution {
        public static ListNode mergeKLists(ListNode[] lists) {
            int length = lists.length;
            if (length == 0)
                return null;
            if (length == 1)
                return lists[0];
//            PriorityQueue<ListNode> heap = new PriorityQueue<>(Comparator.comparingInt(v -> v.val));
            int endIndex = length >> 1;
            //统计已处理完成的桶位数量，等于数组length退出循环
            int finishedCount = 0;
            boolean[] finished = new boolean[length];
            ListNode result = new ListNode(-1, null);
            ListNode pointNode = result;
            while (finishedCount < length) {
                //统计最小值与最小值所在的桶
                int minVal = Integer.MAX_VALUE;
                int minIndex = -1;
                for (int i = 0; i < length; i++) {
                    //判断数组长度奇偶性，奇数个，j=i+1，偶数个i=j，这里指的是遍历数量
                    //奇数个，跳过i，只处理j
                    ListNode listI = lists[i];
                    if (!finished[i]) {
                        if (listI == null) {
                            finished[i] = true;
                            finishedCount++;
                        } else if (listI.val <= minVal) {
                            minIndex = i;
                            minVal = listI.val;
                        }
                    }
                }
                //找到数组中值最小，拼到pointNode.next，去除桶位的头结点
                if (minIndex < 0)
                    continue;
                ListNode currentNode = lists[minIndex].next;
                pointNode.next = lists[minIndex];
                lists[minIndex].next = null;
                lists[minIndex] = currentNode;
                pointNode = pointNode.next;
            }
            return result.next;
        }
    }

    //用堆,速度快
    static class Solution1 {
        public static ListNode mergeKLists(ListNode[] lists) {
            int length = lists.length;
            if (length == 0)
                return null;
            if (length == 1)
                return lists[0];
            PriorityQueue<ListNode> heap = new PriorityQueue<>(Comparator.comparingInt(v -> v.val));
            //统计最小值与最小值所在的桶
            for (int i = 0; i < length; i++) {
                ListNode listNode = lists[i];
                if (listNode != null) {
                    ListNode currentNode = listNode;
                    while (currentNode != null) {
                        heap.add(new ListNode(currentNode.val));
                        currentNode = currentNode.next;
                    }
                }
            }
            //统计已处理完成的桶位数量，等于数组length退出循环
            ListNode result = new ListNode(-1, null);
            ListNode pointNode = result;
            while (!heap.isEmpty()) {
                pointNode.next = heap.poll();
                pointNode = pointNode.next;
            }
            return result.next;
        }
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

        n6.next = n7;
        n7.next = n8;
        n8.next = n9;
        n9.next = n10;
        System.out.println(Solution1.mergeKLists(new ListNode[]{n1, n6, new ListNode()}));
    }
}
