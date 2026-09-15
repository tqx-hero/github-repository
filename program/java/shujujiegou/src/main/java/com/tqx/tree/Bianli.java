package com.tqx.tree;

import java.util.ArrayDeque;

/**
 * @author Administrator
 * @version 1.0
 * @description: 二叉树遍历
 * @date 2026/3/28 9:20
 */
public class Bianli {

    static class Tree {
        char val;
        Tree left;
        Tree right;

        public Tree(char val) {
            this.val = val;
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

    static void bianliStack(Tree tree) {
        ArrayDeque<Tree> stack = new ArrayDeque<>();
        boolean a;
        for (; (a = tree != null) || !stack.isEmpty(); ) {
            if (a) {
                System.out.println(tree.val);
                if (tree.right != null)
                    stack.push(tree.right);
                tree = tree.left;
            } else
                tree = stack.pop();
        }
    }

    //递归遍历
    static void bianli(Tree tree) {
        if (tree == null)
            return;
        System.out.println(tree.val);
        bianli(tree.left);
        bianli(tree.right);
    }


    static Tree initTree() {
        Tree a = new Tree('A');
        Tree b = new Tree('B');
        Tree c = new Tree('C');
        Tree d = new Tree('D');
        Tree e = new Tree('E');
        Tree f = new Tree('F');
        Tree g = new Tree('G');
        Tree h = new Tree('H');
        Tree i = new Tree('I');
        a.left = b;
        a.right = g;
        b.left = e;
        b.right = c;
        g.left = h;
        g.right = i;
        e.right = f;
        c.right = d;
        return a;
    }

    public static void main(String[] args) {
        bianliStack(initTree());
    }

}
