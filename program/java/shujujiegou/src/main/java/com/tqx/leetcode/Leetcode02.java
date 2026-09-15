package com.tqx.leetcode;


/**
 * @author Administrator
 * @version 1.0
 * @description: 力扣2个链表数相加
 * 输入：l1 = [2,4,3], l2 = [5,6,4]
 * 输出：[7,0,8]
 * 解释：342 + 465 = 807.
 * @date 2026/3/26 15:16
 */
public class Leetcode02 {

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

    //    class Solution {
    public static ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        //哨兵节点
        ListNode resNode = new ListNode();
        int add = 0;
        ListNode next;
        for (next = resNode; l1 != null || l2 != null || add != 0; next = next.next) {
            ListNode nex = new ListNode();
            int val1 = 0, val2 = 0;
            if (l1 != null) {
                val1 = l1.val;
                l1 = l1.next;
            }
            if (l2 != null) {
                val2 = l2.val;
                l2 = l2.next;
            }
            int count = val1 + val2 + add;
            add = count / 10;
            nex.val = count % 10;
            next.next = nex;
        }
        return resNode.next;
    }
//    }

    static ListNode[] initListNode() {

        ListNode listNode2 = new ListNode().setVal(2);
        ListNode listNode4 = new ListNode().setVal(4);
        ListNode listNod3 = new ListNode().setVal(7);
        listNode2.next = listNode4;
        listNode4.next = listNod3;

        ListNode listNod5 = new ListNode().setVal(5);
        ListNode listNod6 = new ListNode().setVal(6);
        ListNode listNodn = new ListNode().setVal(4);
        listNod5.next = listNod6;
        listNod6.next = listNodn;


        return new ListNode[]{listNode2, listNod5};
    }

    public static void main(String[] args) {
        System.out.println(addTwoNumbers(initListNode()[0], initListNode()[1]));
    }
}
