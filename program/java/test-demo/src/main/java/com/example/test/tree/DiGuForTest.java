package com.example.test.tree;

import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 递归调用遍历树:深度优先、前序遍历
 * A
 * | \
 * B   C
 * |  |  \
 * D  G   H
 * | \
 * E   F
 * @date 2026/2/27 15:50
 */
public class DiGuForTest {


    /**
     * 前序遍历
     *
     * @param root
     */
    static void foreach(LinkedTree<Object> root) {
        if (Objects.isNull(root)) return;
        System.out.println("数据====" + root.getData());
        foreach(root.getLeft());
        foreach(root.getRight());
    }

    /**
     * 中序遍历
     *
     * @param root
     */
    static void foreachMiddle(LinkedTree<Object> root) {
        if (Objects.isNull(root)) return;
        foreachMiddle(root.getLeft());
        System.out.println("数据====" + root.getData());
        foreachMiddle(root.getRight());
    }

    /**
     * 后序遍历
     *
     * @param root
     */
    static void foreachLast(LinkedTree<Object> root) {
        if (Objects.isNull(root)) return;
        foreachLast(root.getLeft());
        foreachLast(root.getRight());
        System.out.println("数据====" + root.getData());
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
//        DiGuForTest.foreach(tree);
//        System.out.println(tree);
//        DiGuForTest.foreachMiddle(tree);
        DiGuForTest.foreachLast(tree);
    }

}
