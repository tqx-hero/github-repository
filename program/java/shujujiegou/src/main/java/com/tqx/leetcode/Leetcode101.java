package com.tqx.leetcode;

import java.util.ArrayDeque;

/**
 * @author Administrator
 * @version 1.0
 * @description: 101. 对称二叉树
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给你一个二叉树的根节点 root ， 检查它是否轴对称。 
 * 示例 1：
 * 输入：
 * root = [1,2,2,3,4,4,3]
 * 输出：
 * true
 * 示例 2：
 * 输入：
 * root = [1,2,2,null,3,null,3]
 * 输出：
 * false
 *  提示：
 * • 树中节点数目在范围 [1, 1000] 内
 * • -100 <= Node.val <= 100 
 * 进阶：你可以运用递归和迭代两种方法解决这个问题吗？
 * @date 2026/5/11 19:29
 */
public class Leetcode101 {

    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode() {
        }

        TreeNode(int val) {
            this.val = val;
        }

        @Override
        public String toString() {
            return "TreeNode{" +
                    "val=" + val +
                    ", left=" + left +
                    ", right=" + right +
                    '}';
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }

    private static boolean isSymmetric(TreeNode left, TreeNode right) {
        if (left == null && right == null)
            return true;
        else if (left == null || right == null)
            return false;
        //两个节点都不为空，则需要递归查看各个节点的左右子树
        //值不相同则直接返回
        if (left.val != right.val)
            return false;
        if (!isSymmetric(left.left, right.right)) {
            return false;
        }
        return isSymmetric(left.right, right.left);
    }

    public static boolean isSymmetric(TreeNode root) {
        //递归方法
//        return isSymmetric(root.left, root.right);
        //迭代方式
        return isMatch(root);
    }

    private static boolean isMatch(TreeNode root) {
        ArrayDeque<TreeNode> stack = new ArrayDeque<>();
        stack.push(root);
        while (!stack.isEmpty()) {
            TreeNode treeNode = stack.pop();
            TreeNode left = treeNode.left, right = treeNode.right;
            if (left == null && right == null)
                continue;
            else if (left == null || right == null)
                return false;
            //两者都不为空，则取值进行比较
            if (left.val != right.val)
                return false;
            //都相同，则需要将2个节点压栈
            // 并比较left的左子树，right的右子树
            TreeNode node2 = new TreeNode(-1);
            node2.left = left.right;
            node2.right = right.left;
            stack.push(node2);
            TreeNode node = new TreeNode(-1);
            node.left = left.left;
            node.right = right.right;
            stack.push(node);
        }
        return true;
    }

    public static void main(String[] args) {
        TreeNode t1 = new TreeNode(1);
        TreeNode t2 = new TreeNode(2);
        TreeNode t3 = new TreeNode(2);
        TreeNode t4 = new TreeNode(3);
        TreeNode t5 = new TreeNode(3);
        TreeNode t6 = new TreeNode(4);
        TreeNode t7 = new TreeNode(4);
        t1.left = t2;
        t1.right = t3;
        t2.left = t4;
        t2.right = t6;
        t3.left = t7;
        t3.right = t5;
        System.out.println(isSymmetric(t1));

    }
}
