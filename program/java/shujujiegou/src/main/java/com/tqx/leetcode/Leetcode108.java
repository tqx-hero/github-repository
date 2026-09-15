package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 108. 将有序数组转换为二叉搜索树
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 平衡 二叉搜索树。 
 * 示例 1：
 * 输入：
 * nums = [-10,-3,0,5,9]
 * 输出：
 * [0,-3,9,-10,null,5]
 * 解释：
 * [0,-10,5,null,-3,null,9] 也将被视为正确答案：
 * <p>
 * 示例 2：
 * 输入：
 * nums = [1,3]
 * 输出：
 * [3,1]
 * 解释：
 * [1,null,3] 和 [3,1] 都是高度平衡二叉搜索树。
 *  提示：
 * • 1 <= nums.length <= 104
 * • -104 <= nums[i] <= 104
 * • nums 按 严格递增 顺序排列
 * @date 2026/5/11 22:07
 */
public class Leetcode108 {

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


    //根据升序数组递归创建AVL树
    public static TreeNode sortedArrayToBST(int[] nums) {
        return buildTree(nums, 0, nums.length - 1);
    }

    private static TreeNode buildTree(int[] nums, int start, int end) {
        if (start > end)
            return null;
        int mid = start + (end - start) / 2;
        TreeNode treeNode = new TreeNode(nums[mid]);
        treeNode.left = buildTree(nums, start, mid - 1);
        treeNode.right = buildTree(nums, mid + 1, end);
        return treeNode;
    }

    public static void main(String[] args) {
//        int[] nums = {1,3};
        int[] nums = {-10, -3, 0, 5, 9};
//        int[] nums = {-10};
        System.out.println(sortedArrayToBST(nums));
    }
}
