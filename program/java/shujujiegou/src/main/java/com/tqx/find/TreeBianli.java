package com.tqx.find;

import java.util.ArrayDeque;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/3 12:48
 */
public class TreeBianli {

    static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        boolean visited;

        @Override
        public String toString() {
            return "TreeNode{" +
                    "left=" + left +
                    ", val=" + val +
                    ", right=" + right +
                    ", visited=" + visited +
                    '}';
        }

        public TreeNode(int val) {
            this.val = val;
        }
    }

    public static TreeNode build() {
        TreeNode t1 = new TreeNode(45);
        TreeNode t2 = new TreeNode(12);
        TreeNode t3 = new TreeNode(3);
        TreeNode t4 = new TreeNode(37);
        TreeNode t5 = new TreeNode(24);
        TreeNode t6 = new TreeNode(53);
        TreeNode t7 = new TreeNode(100);
        TreeNode t8 = new TreeNode(61);
        TreeNode t9 = new TreeNode(90);
        TreeNode t10 = new TreeNode(78);

        t1.left = t2;
        t1.right = t6;
        t2.left = t3;
        t2.right = t4;
        t4.left = t5;
        t6.right = t7;
        t7.left = t8;
        t8.right = t9;
        t9.left = t10;
        return t1;
    }

    //中序遍历，压栈形式
    public static void middle(TreeNode tree) {
        ArrayDeque<TreeNode> stack = new ArrayDeque<>();
        while (tree != null || !stack.isEmpty()) {
            if (tree != null) {
                stack.push(tree);
                tree = tree.left;
            } else {
                TreeNode treeNode = stack.pop();
                System.out.println("数据:" + treeNode.val);
                tree = treeNode.right;
            }
        }
    }

    //前序遍历
    public static void front(TreeNode tree) {
        ArrayDeque<TreeNode> stack = new ArrayDeque<>();
        while (tree != null || !stack.isEmpty()) {
            if (tree != null) {
                System.out.println("数据：" + tree.val);
                TreeNode right = tree.right;
                if (right != null)
                    stack.push(right);
                tree = tree.left;
            } else {
                tree = stack.pop();
            }
        }
    }

    //后序遍历，一定要注意节点可能会被压两次入栈，需要做好判断
    public static void end(TreeNode tree) {
        ArrayDeque<TreeNode> stack = new ArrayDeque<>();
        while (tree != null || !stack.isEmpty()) {
            if (tree != null) {
                stack.push(tree);
                tree = tree.left;
            } else {
                tree = stack.pop();
                TreeNode right = tree.right;
                if (right != null && !right.visited) {
                    stack.push(tree);
                } else if (!tree.visited) {
                    System.out.println("数据：" + tree.val);
                    tree.visited = true;
                }
                tree = tree.right;
            }
        }
    }

    public static TreeNode findElement(TreeNode tree, int num) {
        while (tree != null) {
            int val = tree.val;
            if (val == num)
                return tree;
            else if (val > num)
                tree = tree.left;
            else
                tree = tree.right;
        }
        return null;
    }

    public static void main(String[] args) {
//        Test.middle(Test.build());
//        Test.front(Test.build());
//        Test.end(Test.build());
//        System.out.println(Test.findElement(Test.build(), 100));
        System.out.println(TreeBianli.getStr("abbaca"));
    }

    public static String getStr(String str) {
        if (str == null || str.isEmpty())
            return "";
        ArrayDeque<Character> stack = new ArrayDeque<>();
        int index = 0;
        while (index < str.length()) {
            char c = str.charAt(index);
            if (!stack.isEmpty()) {
                char sc = stack.peek();
                if (sc == c) {
                    stack.pop();
                    index++;
                    continue;
                }
            }
            stack.push(c);
            index++;
        }

        StringBuilder sb = new StringBuilder();
        for (Character c : stack)
            sb.append(c);
//        while (!stack.isEmpty())
//            sb.append(stack.pop());
        return sb.toString();
    }


}
