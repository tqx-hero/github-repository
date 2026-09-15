package com.tqx.leetcode;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 94. 二叉树的中序遍历
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。 
 * 示例 1：
 * 输入：
 * root = [1,null,2,3]
 * 输出：
 * [1,3,2]
 * 示例 2：
 * 输入：
 * root = []
 * 输出：
 * []
 * 示例 3：
 * 输入：
 * root = [1]
 * 输出：
 * [1]
 *  提示：
 * • 树中节点数目在范围 [0, 100] 内
 * • -100 <= Node.val <= 100
 * @date 2026/5/11 18:24
 */
public class Leetcode94 {

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

    //压栈中序遍历
    public static List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> list = new ArrayList<>();
        if (root == null)
            return list;
        ArrayDeque<TreeNode> stack = new ArrayDeque<>();
        TreeNode cur = root;
        while (cur != null || !stack.isEmpty()) {
            //不为空则将其压入栈内
            //令cur=cur.left，继续遍历左子树
            if (cur != null) {
                stack.push(cur);
                cur = cur.left;
            }
            //cur为空时，说明左子树都压完了。
            //弹栈后将其放入List，开始压右子树
            else {
                TreeNode curNode = stack.pop();
                list.add(curNode.val);
                cur = curNode.right;
            }
        }
        return list;
    }

    public static void main(String[] args) {
        TreeNode t1 = new TreeNode(1);
        TreeNode t2 = new TreeNode(2);
        TreeNode t3 = new TreeNode(3);
//        TreeNode t4 = new TreeNode(4);
//        TreeNode t5 = new TreeNode(5);
//        TreeNode t6 = new TreeNode(6);
//        TreeNode t7 = new TreeNode(7);
//        TreeNode t8 = new TreeNode(8);
        t1.right = t2;
        t2.left = t3;
        System.out.println(inorderTraversal(null));
    }

}
