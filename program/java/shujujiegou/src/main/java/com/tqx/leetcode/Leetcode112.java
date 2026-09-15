package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 112. 路径总和
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。
 * 叶子节点 是指没有子节点的节点。 
 * 示例 1：
 * 输入：
 * root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
 * 输出：
 * true
 * 解释：
 * 等于目标和的根节点到叶节点路径如上图所示。
 * 示例 2：
 * 输入：
 * root = [1,2,3], targetSum = 5
 * 输出：
 * false
 * 解释：
 * 树中存在两条根节点到叶子节点的路径：
 * (1 --> 2): 和为 3
 * (1 --> 3): 和为 4
 * 不存在 sum = 5 的根节点到叶子节点的路径。
 * 示例 3：
 * 输入：
 * root = [], targetSum = 0
 * 输出：
 * false
 * 解释：
 * 由于树是空的，所以不存在根节点到叶子节点的路径。
 *  提示：
 * • 树中节点的数目在范围 [0, 5000] 内
 * • -1000 <= Node.val <= 1000
 * • -1000 <= targetSum <= 1000
 * @date 2026/5/12 21:40
 */
public class Leetcode112 {

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

    public static boolean hasPathSum(TreeNode root, int targetSum) {
        if (root == null)
            return false;
        try {
            pathSum(root, 0, targetSum);
            return false;
        } catch (IllegalArgumentException e) {
            return true;
        }
    }

    private static void pathSum(TreeNode cur, int total, int targetSum) throws IllegalArgumentException {
        total += cur.val;
        //自顶向下加，直到叶子节点时判断路径和是否与目标值相等
        if (cur.left == null && cur.right == null) {
            if (total == targetSum)
                throw new IllegalArgumentException("找到了");
            else return;
        }
        if (cur.left != null)
            pathSum(cur.left, total, targetSum);
        if (cur.right != null)
            pathSum(cur.right, total, targetSum);
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
//        t1.right = t3;
//        t2.left = t4;
//        t2.right = t5;
//        t5.left = t6;
        System.out.println(hasPathSum(t1, 1));
    }
}
