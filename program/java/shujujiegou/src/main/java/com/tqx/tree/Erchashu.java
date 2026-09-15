package com.tqx.tree;

/**
 * @author Administrator
 * @version 1.0
 * @description: 二叉树
 * @date 2026/4/3 15:22
 */
public class Erchashu {

    static class TreeNode {
        EleNode keyVal;
        TreeNode left;
        TreeNode right;

        public TreeNode(EleNode keyVal) {
            this.keyVal = keyVal;
        }

        @Override
        public String toString() {
            return "TreeNode{" +
                    "keyVal=" + keyVal +
                    ", left=" + left +
                    ", right=" + right +
                    '}';
        }
    }

    static class EleNode {
        int keyVal;
        Object values;

        public EleNode(int keyVal) {
            this.keyVal = keyVal;
        }

        @Override
        public String toString() {
            return "EleNode{" +
                    "keyVal=" + keyVal +
                    ", values=" + values +
                    '}';
        }
    }

    private void add(TreeNode root, int val) {
        //小的去左子树查找，插入叶子结点
        TreeNode treeNode = root;
        TreeNode prevNode = null;
        while (treeNode != null) {
            int rootKey = treeNode.keyVal.keyVal;
            if (rootKey == val)
                return;
            prevNode = treeNode;
            if (rootKey > val) {
                treeNode = treeNode.left;
            } else {
                treeNode = treeNode.right;
            }
        }
        TreeNode node = new TreeNode(new EleNode(val));
        if (prevNode.keyVal.keyVal > val)
            prevNode.left = node;
        else
            prevNode.right = node;
    }
    //创建二叉排序树
    public TreeNode create(int[] arr) {
        //{45,24,53,45,12,24,90}
        if (arr == null || arr.length == 0)
            return null;
        //增加第一个为头结点
        TreeNode root = new TreeNode(new EleNode(arr[0]));
        for (int i = 1; i < arr.length; i++) {
            add(root, arr[i]);
        }
        return root;
    }

    public static void main(String[] args) {
        int[] arr = {45, 24, 53, 45, 12, 24, 90};
        Erchashu erchashu = new Erchashu();
        System.out.println(erchashu.create(arr));
    }
}
