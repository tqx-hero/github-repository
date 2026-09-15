package com.example.test.erfenfa;


import java.util.Map;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 递归查询BST（平衡二叉树）下符合条件的数据
 * @date 2026/2/28 10:29
 */
public class DiGuiSearchBST {

    /**
     * 定义一个树
     */
    static class TreeNode {
        int val;
        TreeNode left;

        public TreeNode(int val) {
            this.val = val;
        }

        @Override
        public String toString() {
            return "TreeNode{" +
                    "left=" + left +
                    ", val=" + val +
                    ", right=" + right +
                    '}';
        }

        public TreeNode() {
        }

        public TreeNode(TreeNode left, TreeNode right, int val) {
            this.left = left;
            this.right = right;
            this.val = val;
        }

        TreeNode right;
    }

    static int count = 0;

    /**
     * 递归调用查询平衡二叉树数据
     *
     * @param target
     * @param tree
     * @return
     */
    static TreeNode get(int target, TreeNode tree) {
        int val = tree.val;
        count++;
        if (target == val) {
            System.out.println("查询次数===" + count);
            return tree;
        }
        if (target < val) {
            tree = tree.left;
        } else {
            tree = tree.right;
        }
        tree = get(target, tree);
        return tree;
    }

    /**
     * 添加操作
     *
     * @param tree
     * @param val
     * @return
     */
    static TreeNode add(TreeNode tree, int val) {
        if (Objects.isNull(tree)) return new TreeNode(val);
        int nodeVal = tree.val;
        if (val == nodeVal) return tree;
        if (val < nodeVal) {
//            //如果查询的节点下方没有子节点，则进行插入操作，否则继续往下遍历
            tree.left = add(tree.left, val);
        } else {
            //如果查询的节点下方没有子节点，则进行插入操作，否则继续往下遍历
            tree.right = add(tree.right, val);
        }
        return tree;
    }


    static TreeNode del(TreeNode tree, int val) {
        if (Objects.isNull(tree)) return null;
        int nodeVal = tree.val;
        if (val == nodeVal) {
            //1、子节点为0或为1个
            if (Objects.isNull(tree.left)) return tree.right;
            if (Objects.isNull(tree.right)) return tree.left;
            //子节点为2个都有
            TreeNode left = tree.left;
            while (left.right != null) {
                left = left.right;
            }
            tree.val = left.val;
            //删除这个节点
            tree.left = del(left, left.val);
        } else if (val < nodeVal) {
            tree.left = del(tree.left, val);
        } else {
            tree.right = del(tree.right, val);
        }
        return tree;
    }


    public static void main(String[] args) {
        //构建树
        TreeNode three = new TreeNode(null, null, 3);
        TreeNode seven = new TreeNode(null, null, 7);
        TreeNode five = new TreeNode(three, seven, 5);

        TreeNode twove = new TreeNode(null, null, 12);
        TreeNode eighth = new TreeNode(null, null, 18);
        TreeNode fifth = new TreeNode(twove, eighth, 15);

        TreeNode root = new TreeNode(five, fifth, 10);
//        System.out.println(root);

        //查找7
//        TreeNode node = DiGuiSearchBST.get(7, root);
//        System.out.println(node);

//        TreeNode treeNode = DiGuiSearchBST.add(root, 20);
//        TreeNode treeNode = DiGuiSearchBST.add(root, 6);
//        System.out.println("添加操作=" + treeNode);
        DiGuiSearchBST.del(root,15);
        System.out.println("添加后的根节点=" + root);
    }

}
