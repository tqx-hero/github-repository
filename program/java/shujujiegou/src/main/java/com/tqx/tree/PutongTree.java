package com.tqx.tree;

import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;

/**
 * @author Administrator
 * @version 1.0
 * @description: 普通树的遍历
 * @date 2026/3/28 10:19
 */
public class PutongTree {

    static class PTree {
        char val;
        PTree prev;
        Set<PTree> next;

        public PTree(char val) {
            this.val = val;
            next = new LinkedHashSet<>();
        }

        @Override
        public String toString() {
            return "PTree{" +
                    "next=" + next +
                    ", val=" + val +
                    ", prev=" + prev +
                    '}';
        }
    }

    static PTree initTree() {
        PTree a = new PTree('A');
        PTree b = new PTree('B');
        PTree c = new PTree('C');
        PTree d = new PTree('D');
        PTree e = new PTree('E');
        PTree f = new PTree('F');

        a.next.add(b);
        a.next.add(c);
        a.next.add(d);
        b.next.add(e);
        b.next.add(f);
        return a;
    }

    //先序遍历
    static void firstOrder(PTree tree) {
        if (tree == null)
            return;
        System.out.println(tree.val);
        tree.next.forEach(PutongTree::firstOrder);
    }

    public static void main(String[] args) {
        firstOrder(initTree());
    }

}
