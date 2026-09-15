package com.tqx.tree;

import java.util.ArrayDeque;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 深度优先
 * @date 2026/3/26 7:47
 */
public class Shenduyouxian {

    private static final ArrayDeque<Tree> QUEUE = new ArrayDeque<>();

    static class Tree {
        String val;
        Tree left;
        Tree right;
        boolean visited;

        @Override
        public String toString() {
            return "Tree{" +
                    "left=" + left +
                    ", val='" + val + '\'' +
                    ", right=" + right +
                    ", visited=" + visited +
                    '}';
        }

        public Tree setVal(String val) {
            this.val = val;
            return this;
        }
    }

    static Tree initTree() {
        Tree a = new Tree().setVal("A");
        Tree b = new Tree().setVal("B");
        Tree c = new Tree().setVal("C");
        Tree d = new Tree().setVal("D");
        Tree e = new Tree().setVal("E");
        Tree f = new Tree().setVal("F");
        Tree g = new Tree().setVal("G");

        a.left = b;
        a.right = e;

        b.left = c;
        b.right = d;

        e.left = f;
        e.right = g;
        return a;
    }

    public static void main(String[] args) {
//        System.out.println(initTree());
//        look(initTree());
        before(initTree());
//        middle(initTree());
//        last(initTree());
    }

    //后序遍历
    static void last(Tree tree) {
        boolean a;
        for (; (a = Objects.nonNull(tree)) || !QUEUE.isEmpty(); ) {
            if (a) {
                QUEUE.push(tree);
                tree = tree.left;
            } else {
                Tree pop = QUEUE.pop();
                if (Objects.nonNull(pop.right) && !pop.right.visited) {
                    QUEUE.push(pop);
                    tree = pop.right;
                } else {
                    if (!pop.visited) {
                        pop.visited = true;
                        System.out.println(pop.val);
                    }
                }
            }
        }
    }

    //中序遍历
    static void middle(Tree tree) {
        boolean a;
        for (; (a = Objects.nonNull(tree)) || !QUEUE.isEmpty(); ) {
            if (a) {
                QUEUE.push(tree);
                tree = tree.left;
            } else {
                Tree pop = QUEUE.pop();
                System.out.println(pop.val);
                tree = pop.right;
            }
        }
    }

    //前序遍历，栈方法
    static void before(Tree tree) {
        boolean a;
        for (; (a = Objects.nonNull(tree)) || !QUEUE.isEmpty(); ) {
            if (a) {
                System.out.println(tree.val);
                if (Objects.nonNull(tree.right)) {
                    QUEUE.push(tree.right);
                }
                tree = tree.left;
            } else {
                tree = QUEUE.pop();
            }
        }

//        for (; ; ) {
//            if (Objects.isNull(tree)) {
//                if (!QUEUE.isEmpty()) {
//                    tree = QUEUE.pop();
//                    continue;
//                }
//                break;
//            }
//            System.out.println(tree.val);
//            Tree right = tree.right;
//            Tree left = tree.left;
//            if (Objects.nonNull(right)) {
//                QUEUE.push(right);
//            }
//            tree = left;
//        }

    }


    //递归遍历
    static void look(Tree tree) {
        if (Objects.isNull(tree)) {
            return;
        }
        look(tree.left);
        look(tree.right);
        System.out.println(tree.val);
    }

}
