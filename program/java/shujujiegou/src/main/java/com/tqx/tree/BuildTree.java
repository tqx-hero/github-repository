package com.tqx.tree;

import java.lang.invoke.VarHandle;
import java.util.HashMap;
import java.util.Objects;
import java.util.Scanner;

/**
 * @author Administrator
 * @version 1.0
 * @description: 按字符顺序构建二叉树
 * @date 2026/3/26 11:11
 */
public class BuildTree {


    public int[] twoSum(int[] nums, int target) {
        int[] res = new int[2];
        HashMap<Integer, Integer> map = new HashMap<>(nums.length);
        for (int i = 0; i < nums.length; i++) {
            int want = target - nums[i];
            if (map.containsKey(want)) {
                res[0] = i;
                res[1] = map.get(want);
                break;
            } else {
                map.put(nums[i], i);
            }
        }
        return res;
    }

    static class Tree {
        char val;
        Tree left;
        Tree right;

        public Tree setVal(char val) {
            this.val = val;
            return this;
        }

        @Override
        public String toString() {
            return "Tree{" +
                    "left=" + left +
                    ", val=" + val +
                    ", right=" + right +
                    '}';
        }
    }

    private static Scanner sc = new Scanner(System.in);

//    static void buildTree(Tree tree) {
//        char s = sc.nextLine().toCharArray()[0];
//        if (s == '#') {
//            return null;
//        } else {
//            if (Objects.isNull(tree)) {
//                tree = new Tree().setVal(s);
//            }
//            buildTree(tree.left);
//            buildTree(tree.right);
//        }
//    }

    // 先序遍历： ABC##DE#G##F###
//    static void bulid(String str) {
//        if (Objects.isNull(str)) {
//            return;
//        }
//        char[] array = str.toCharArray();
//        Tree tree = new Tree();
//        for (char a : array) {
//            buildTree(a, tree);
//        }
//
//    }

    public static void main(String[] args) {
//        Tree tree = buildTree(null);
//        System.out.println(tree);
    }


}
