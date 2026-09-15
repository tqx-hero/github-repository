package com.tqx.leetcode;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 链表删除
 * 输入：head = [1,2,3,4,5], n = 2
 * 输出：[1,2,3,5]
 * 示例 2：
 * <p>
 * 输入：head = [1], n = 1
 * 输出：[]
 * 示例 3：
 * <p>
 * 输入：head = [1,2], n = 1
 * 输出：[1]
 * <p>
 * <p>
 * 提示：
 * <p>
 * 链表中结点的数目为 sz
 * 1 <= sz <= 30
 * 0 <= Node.val <= 100
 * 1 <= n <= sz
 * <p>
 * <p>
 * 进阶：你能尝试使用一趟扫描实现吗？
 * @date 2026/4/2 4:43
 */
public class Leetcode19 {

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

        public static ListNode removeNthFromEnd(ListNode head, int n) {
            List<ListNode> list = new ArrayList<>();
            ListNode currentNode = head;
            //放入集合，获取
            while (currentNode != null) {
                list.add(currentNode);
                currentNode = currentNode.next;
            }
            int totalCount = list.size();
            if (totalCount == 1)
                return null;
            //截取长度=总长度，返回null
            int currentIndex = totalCount - n;
            if (currentIndex == 0)
                return list.get(1);
            //获取倒数第n个节点与n的前驱节点
            ListNode nodePrev = list.get(currentIndex - 1);
            ListNode removeNode = list.get(currentIndex);
            nodePrev.next = removeNode.next;
            removeNode.next = null;
            return head;
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
        return n1;
    }

    public static void main(String[] args) {
//        System.out.println(createNode());
        ListNode node = createNode();
        System.out.println(Solution.removeNthFromEnd(node, 5));
    }
}
