package com.example.test.tree;

import com.example.test.que.ArrayQueueDemo;

import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 广度优先遍历二叉树，使用队列
 * @date 2026/2/27 19:41
 */
public class TreeListByQueue {

    /**
     * 广度优先遍历二叉树 ，使用队列
     *
     * @param tree
     */
    static void itertor(LinkedTree<Object> tree) {
        ArrayQueueDemo demo = new ArrayQueueDemo();
        demo.add(tree);
        while (!demo.isEmpty()) {
            LinkedTree<Object> peek = (LinkedTree<Object>) demo.peek();
            System.out.println(peek.getData());
            if (Objects.nonNull(peek.getLeft())) {
                demo.add(peek.getLeft());
            }
            if (Objects.nonNull(peek.getRight())) {
                demo.add(peek.getRight());
            }
            demo.del();
        }
    }

    public static void main(String[] args) {
        LinkedTree<Object> tree = new LinkedTree<>();
        tree.addRoot("A");
        LinkedTree<Object> treeC = tree.addRight(tree, "C");
        LinkedTree<Object> treeB = tree.addLeft(tree, "B");
        LinkedTree<Object> treeD = tree.addLeft(treeB, "D");
        tree.addLeft(treeD, "E");
        tree.addRight(treeD, "F");
        tree.addLeft(treeC, "G");
        tree.addRight(treeC, "H");
        TreeListByQueue.itertor(tree);
    }

}
