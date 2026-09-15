package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 100. 相同的树
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。
 * 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。 
 * 示例 1：
 * 输入：
 * p = [1,2,3], q = [1,2,3]
 * 输出：
 * true
 * 示例 2：
 * 输入：
 * p = [1,2], q = [1,null,2]
 * 输出：
 * false
 * 示例 3：
 * 输入：
 * p = [1,2,1], q = [1,1,2]
 * 输出：
 * false
 *  提示：
 * • 两棵树上的节点数目都在范围 [0, 100] 内
 * • -104 <= Node.val <= 104
 * @date 2026/5/11 18:44
 */
public class Leetcode100 {

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

    public static boolean isSameTree(TreeNode p, TreeNode q) {
        TreeNode pPtr = p, qPtr = q;
        if (pPtr == null && qPtr == null)
            return true;
        else if (pPtr != null && qPtr != null) {
            //不相同则直接返回
            if (pPtr.val != qPtr.val)
                return false;
            //相同则前序遍历
            if (!isSameTree(pPtr.left, qPtr.left))
                return false;
            return isSameTree(pPtr.right, qPtr.right);
        } else
            return false;
    }

    public static void main(String[] args) {
        TreeNode t1 = new TreeNode(1);
        TreeNode t2 = new TreeNode(2);
        TreeNode t3 = new TreeNode(3);
        t1.right = t2;
        t2.left = t3;
        System.out.println(isSameTree(t1, t1));
    }
}
