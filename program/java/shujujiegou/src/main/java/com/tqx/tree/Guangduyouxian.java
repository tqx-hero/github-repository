package com.tqx.tree;

import java.util.ArrayDeque;
import java.util.Objects;
import java.util.Queue;

/**
 * @author Administrator
 * @version 1.0
 * @description: 广度优先
 * @date 2026/3/26 9:53
 */
public class Guangduyouxian {

    private static final ArrayDeque<Tree> QUEUE = new ArrayDeque<>();


    static class Tree {
        String val;
        Tree left;
        Tree right;

        public Tree setVal(String val) {
            this.val = val;
            return this;
        }

        @Override
        public String toString() {
            return "Tree{" +
                    "left=" + left +
                    ", val='" + val + '\'' +
                    ", right=" + right +
                    '}';
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

    //用队列实现
    static void guang(Tree tree) {
        for (QUEUE.add(tree); !QUEUE.isEmpty(); ) {
            Tree poll = QUEUE.poll();
            System.out.println(poll.val);
            if (Objects.nonNull(poll.left)) {
                QUEUE.add(poll.left);
            }
            if (Objects.nonNull(poll.right)) {
                QUEUE.add(poll.right);
            }
        }
    }

    public static void main(String[] args) {
        guang(initTree());
    }

}
