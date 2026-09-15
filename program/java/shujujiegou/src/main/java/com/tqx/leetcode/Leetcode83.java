package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 83. 删除排序链表中的重复元素
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次 。返回 已排序的链表 。 
 * 示例 1：
 * 输入：
 * head = [1,1,2]
 * 输出：
 * [1,2]
 * 示例 2：
 * 输入：
 * head = [1,1,2,3,3]
 * 输出：
 * [1,2,3]
 *  提示：
 * • 链表中节点数目在范围 [0, 300] 内
 * • -100 <= Node.val <= 100
 * • 题目数据保证链表已经按升序 排列
 * @date 2026/5/10 23:19
 */
public class Leetcode83 {

    /**
     * Definition for singly-linked list.
     * public class ListNode {
     * int val;
     * ListNode next;
     * ListNode() {}
     * ListNode(int val) { this.val = val; }
     * ListNode(int val, ListNode next) { this.val = val; this.next = next; }
     * }
     */

    static class ListNode {
        int val;
        ListNode next;

        public ListNode setVal(int val) {
            this.val = val;
            return this;
        }

        @Override
        public String toString() {
            return "ListNode{" +
                    "next=" + next +
                    ", val=" + val +
                    '}';
        }

        ListNode() {
        }

        ListNode(int val) {
            this.val = val;
        }

        ListNode(int val, ListNode next) {
            this.val = val;
            this.next = next;
        }
    }

    public static ListNode deleteDuplicates(ListNode head) {
        if (head == null)
            return head;
        ListNode slow = head, quick = head.next;
        while (quick != null) {
            //如果两指针指向的节点数据不一致，slow->quick，
            //且slow =quick，quick前移
            if (slow.val != quick.val) {
                slow.next = quick;
                slow = quick;
            } else if (slow.next != null) {
                slow.next = null;
            }
            //如果数据一致，则quick前移，一直找到与slow不相同的，再去连接
            quick = quick.next;
        }
        return head;
    }

    public static void main(String[] args) {
        ListNode l1 = new ListNode(1);
        ListNode l2 = new ListNode(1);
        ListNode l3 = new ListNode(2);
        ListNode l4 = new ListNode(3);
        ListNode l5 = new ListNode(3);

        l1.next = l2;
        l2.next = l3;
        l3.next = l4;
        l4.next = l5;
        System.out.println(deleteDuplicates(l1));
    }
}
