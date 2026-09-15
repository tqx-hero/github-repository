package com.tqx.order;

/**
 * @author Administrator
 * @version 1.0
 * @description: 两个有序链表升序生成新链表
 * @date 2026/4/7 11:58
 */
public class TwoLinkedUnion {

    static class Node {
        int val;
        Node next;

        public Node(int val) {
            this.val = val;
        }

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

    public static Node order(Node n1, Node n2) {
        //定义两个指针分别指向两个链表
        Node newNode = new Node(-1);
        Node curNode = newNode;
        while (n1 != null && n2 != null) {
            if (n1.val < n2.val) {
                curNode.next = n1;
                n1 = n1.next;
            } else {
                curNode.next = n2;
                n2 = n2.next;
            }
            curNode = curNode.next;
        }
        curNode.next = n1 == null ? n2 : n1;
        return newNode.next;
    }

    public static void main(String[] args) {
        Node node1 = new Node(1);
        Node node2 = new Node(2);
        Node node3 = new Node(3);
        Node node4 = new Node(4);

        node1.next=node2;
        node2.next=node3;
        node3.next=node4;

        Node node5 = new Node(5);
        Node node6 = new Node(6);
        Node node7 = new Node(7);
        Node node8 = new Node(8);
        Node node9 = new Node(9);
        node5.next=node6;
        node6.next=node7;
        node7.next=node8;
        node8.next=node9;
        System.out.println(TwoLinkedUnion.order(node1, node5));
    }
}
