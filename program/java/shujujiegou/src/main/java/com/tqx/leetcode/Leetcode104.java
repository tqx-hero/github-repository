package com.tqx.leetcode;

import java.util.ArrayDeque;

/**
 * @author Administrator
 * @version 1.0
 * @description: ￼
 * 代码
 * ￼
 * 测试用例
 * 测试用例
 * ￼
 * 测试结果
 * 104. 二叉树的最大深度
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给定一个二叉树 root ，返回其最大深度。
 * 二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。 
 * 示例 1： 
 * 输入：
 * root = [3,9,20,null,null,15,7]
 * 输出：
 * 3
 * 示例 2：
 * 输入：
 * root = [1,null,2]
 * 输出：
 * 2
 *  提示：
 * • 树中节点的数量在 [0, 104] 区间内。
 * • -100 <= Node.val <= 100
 * @date 2026/5/11 21:27
 */
public class Leetcode104 {

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

    private static class ExtNode {
        int depth;
        TreeNode treeNode;

        public ExtNode(int depth, TreeNode treeNode) {
            this.depth = depth;
            this.treeNode = treeNode;
        }

        public ExtNode(TreeNode treeNode) {
            this.treeNode = treeNode;
        }
    }

//    public static int maxDepth(TreeNode root) {
//        if (root == null)
//            return 0;
//        int max = 0;
//        ArrayDeque<ExtNode> queue = new ArrayDeque<>();
//        queue.offer(new ExtNode(1, root));
//        while (!queue.isEmpty()) {
//            ExtNode extNode = queue.poll();
//            int depth = extNode.depth;
//            //更新最大深度
//            if (depth > max)
//                max = depth;
//            TreeNode treeNode = extNode.treeNode;
//            TreeNode left = treeNode.left;
//            TreeNode right = treeNode.right;
//            //如果有孩子节点
//            //新建孩子节点并更新它的深度
//            if (left != null)
//                queue.offer(new ExtNode(depth + 1, left));
//            if (right != null)
//                queue.offer(new ExtNode(depth + 1, right));
//        }
//        return max;
//    }

    public static int maxDepth(TreeNode root) {
        if (root == null)
            return 0;
        int leftMax = maxDepth(root.left);
        int rightMax = maxDepth(root.right);
        return Math.max(leftMax, rightMax) + 1;
    }

    public static void main(String[] args) {
        TreeNode t1 = new TreeNode(1);
        TreeNode t2 = new TreeNode(2);
        TreeNode t3 = new TreeNode(2);
        TreeNode t4 = new TreeNode(3);
        TreeNode t5 = new TreeNode(3);
        TreeNode t6 = new TreeNode(4);
        TreeNode t7 = new TreeNode(4);
        TreeNode t8 = new TreeNode(5);
        t1.left = t2;
        t1.right = t3;
        t2.left = t4;
        t2.right = t6;
        t3.left = t7;
        t3.right = t5;
        t5.left = t8;
        System.out.println(maxDepth(t1));
    }
}
