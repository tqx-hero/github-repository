package com.example.test.tree;

import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个链表结构组成的树
 * @date 2026/2/27 14:56
 */
public class LinkedTree<E> {

    private E data;
    private LinkedTree<E> left;
    private LinkedTree<E> right;

    public E getData() {
        return data;
    }

    public void setData(E data) {
        this.data = data;
    }

    public LinkedTree<E> getLeft() {
        return left;
    }

    public void setLeft(LinkedTree<E> left) {
        this.left = left;
    }

    public LinkedTree<E> getRight() {
        return right;
    }

    public void setRight(LinkedTree<E> right) {
        this.right = right;
    }

    public LinkedTree(E data) {
        this.data = data;
    }

    void addRoot(E data) {
        this.data = data;
    }

    public LinkedTree() {
    }

    LinkedTree<E> addLeft(LinkedTree<E> parTree, E d) {
        if (Objects.isNull(parTree))
            throw new IllegalArgumentException("父节点不允许为空！");
        LinkedTree<E> resTree = new LinkedTree<>(d);
        parTree.left = resTree;
        return resTree;
    }

    @Override
    public String toString() {
        return "LinkedTree{" +
                "data=" + data +
                ", left=" + left +
                ", right=" + right +
                '}';
    }

    LinkedTree<E> addRight(LinkedTree<E> parTree, E d) {
        if (Objects.isNull(parTree))
            throw new IllegalArgumentException("父节点不允许为空！");
        LinkedTree<E> resTree = new LinkedTree<>(d);
        parTree.right = resTree;
        return resTree;
    }


    public static void main(String[] args) {
        LinkedTree<Object> tree = new LinkedTree<>();
        tree.addRoot("root");

        tree.addLeft(tree, "left1");
        tree.addRight(tree, "right1");
        System.out.println(tree);
    }

}
