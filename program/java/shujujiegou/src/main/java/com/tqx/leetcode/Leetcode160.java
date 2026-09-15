package com.tqx.leetcode;

import java.util.HashSet;
import java.util.Set;

/**
 * @author Administrator
 * @version 1.0
 * @description: 160. 相交链表
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。
 * 图示两个链表在节点 c1 开始相交：
 * ￼
 * 题目数据 保证 整个链式结构中不存在环。
 * 注意，函数返回结果后，链表必须 保持其原始结构 。
 * 自定义评测：
 * 评测系统 的输入如下（你设计的程序 不适用 此输入）：
 * • intersectVal - 相交的起始节点的值。如果不存在相交节点，这一值为 0
 * • listA - 第一个链表
 * • listB - 第二个链表
 * • skipA - 在 listA 中（从头节点开始）跳到交叉节点的节点数
 * • skipB - 在 listB 中（从头节点开始）跳到交叉节点的节点数
 * 评测系统将根据这些输入创建链式数据结构，并将两个头节点 headA 和 headB 传递给你的程序。如果程序能够正确返回相交节点，那么你的解决方案将被 视作正确答案 。
 * 提示：
 * • listA 中节点数目为 m
 * • listB 中节点数目为 n
 * • 1 <= m, n <= 3 * 104
 * • 1 <= Node.val <= 105
 * • 0 <= skipA <= m
 * • 0 <= skipB <= n
 * • 如果 listA 和 listB 没有交点，intersectVal 为 0
 * • 如果 listA 和 listB 有交点，intersectVal == listA[skipA] == listB[skipB] 
 * 进阶：你能否设计一个时间复杂度 O(m + n) 、仅用 O(1) 内存的解决方案？
 * @date 2026/5/13 21:14
 */
public class Leetcode160 {
    private static class ListNode {
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

    //双指针，一个为null后指向另一个头结点继续遍历
    //如果两者相同，则返回，否则两者都为null，表示没有相交
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        ListNode ha = headA, hb = headB;
        while (ha != hb) {
            ha = ha == null ? headB : ha.next;
            hb = hb == null ? headA : hb.next;
        }
        return ha;
    }

    public static void main(String[] args) {
        ListNode l1 = new ListNode(2);
        ListNode l2 = new ListNode(2);
        ListNode l3 = new ListNode(2);
        ListNode l4 = new ListNode(2);
        ListNode l5 = new ListNode(2);
        ListNode l6 = new ListNode(2);
    }
}
