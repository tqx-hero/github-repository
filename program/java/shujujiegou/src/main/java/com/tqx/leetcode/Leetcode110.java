package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 110. 平衡二叉树
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给定一个二叉树，判断它是否是 平衡二叉树   
 * 示例 1：
 * 输入：
 * root = [3,9,20,null,null,15,7]
 * 输出：
 * true
 * 示例 2：
 * 输入：
 * root = [1,2,2,3,3,null,null,4,4]
 * 输出：
 * false
 * 示例 3：
 * 输入：
 * root = []
 * 输出：
 * true
 *  提示：
 * • 树中的节点数在范围 [0, 5000] 内
 * • -104 <= Node.val <= 104
 * @date 2026/5/12 18:53
 */
public class Leetcode110 {

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

    public static boolean isBalanced(TreeNode root) {
        if (root == null)
            return true;
        try {
            height(root);
            return true;
        } catch (IndexOutOfBoundsException e) {
            return false;
        }
    }

    private static int height(TreeNode node) throws IndexOutOfBoundsException {
        if (node == null)
            return -1;
        //不为空
        int lh = height(node.left);
        int lr = height(node.right);
        if (Math.abs(lh - lr) <= 1)
            return Math.max(lh, lr) + 1;
        else
            throw new IndexOutOfBoundsException("不是平衡二叉树");
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
//        t3.left = t7;
//        t3.right = t5;
//        t5.left = t8;
        System.out.println(isBalanced(null));

    }

}
