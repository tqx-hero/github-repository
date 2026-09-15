package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 206. 反转链表
 * 简单
 * 相关标签
 * premium lock icon
 * 相关企业
 * 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * <p>
 * 输入：head = [1,2,3,4,5]
 * 输出：[5,4,3,2,1]
 * 示例 2：
 * <p>
 * <p>
 * 输入：head = [1,2]
 * 输出：[2,1]
 * 示例 3：
 * <p>
 * 输入：head = []
 * 输出：[]
 * <p>
 * <p>
 * 提示：
 * <p>
 * 链表中节点的数目范围是 [0, 5000]
 * -5000 <= Node.val <= 5000
 * <p>
 * <p>
 * 进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
 * @date 2026/5/11 23:23
 */
public class Leetcode206 {

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

    //翻转链表
//    public ListNode reverseList(ListNode head) {
//        if (head == null)
//            return null;
//        ListNode cur = head, prev = null;
//        while (cur != null) {
//            ListNode next = cur.next;
//            cur.next = prev;
//            prev = cur;
//            cur = next;
//        }
//        return prev;
//    }
    //递归实现
    public static ListNode reverseList(ListNode head) {
        return reverse(head, null);
    }

    private static ListNode reverse(ListNode cur, ListNode next) {
        if (cur == null)
            return next;
        ListNode nt = cur.next;
        cur.next = next;
        return reverse(nt, cur);
    }

    public static void main(String[] args) {
        ListNode l1 = new ListNode(1);
        ListNode l2 = new ListNode(2);
        ListNode l3 = new ListNode(3);
        ListNode l4 = new ListNode(4);
        l1.next=l2;
        l2.next=l3;
        l3.next=l4;
        System.out.println(reverseList(l4));
    }
}
