package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 111. 二叉树的最小深度
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给定一个二叉树，找出其最小深度。
 * 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
 * 说明：叶子节点是指没有子节点的节点。 
 * 示例 1：
 * 输入：
 * root = [3,9,20,null,null,15,7]
 * 输出：
 * 2
 * 示例 2：
 * 输入：
 * root = [2,null,3,null,4,null,5,null,6]
 * 输出：
 * 5
 *  提示：
 * • 树中节点数的范围在 [0, 105] 内
 * • -1000 <= Node.val <= 1000
 * @date 2026/5/12 19:39
 */
public class Leetcode111 {

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

    public static int minDepth(TreeNode root) {
        if (root == null)
            return 0;
        int hl = minDepth(root.left);
        int hr = minDepth(root.right);
        if (hl == 0 && hr == 0)
            return 1;
        else if (hl == 0 || hr == 0)
            return Math.max(hl, hr) + 1;
        else
            return Math.min(hl, hr) + 1;
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
        t2.right = t5;
        t5.left = t6;
        System.out.println(minDepth(t1));
    }
}
