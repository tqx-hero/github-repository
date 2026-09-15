package com.example.test.tree;

import java.util.Arrays;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个二叉树，底层由数组实现
 * @date 2026/2/27 14:16
 */
public class ArrayTree {

    private Object[] tree;
    private int parent;

    private int max_compactiy = 10;

    public ArrayTree() {
        parent = 0;
        tree = new Object[max_compactiy];
    }

    @Override
    public String toString() {
        return "ArrayTree{" +
                "max_compactiy=" + max_compactiy +
                ", tree=" + Arrays.toString(tree) +
                ", parent=" + parent +
                '}';
    }

    /**
     * 放入根节点
     *
     * @param root
     */
    void putRoot(Object root) {
        if (Objects.isNull(root))
            throw new IllegalArgumentException("root is null");
        tree[0] = root;
    }

    void putLeft(int pareIdx, Object value) {
        int idx = (pareIdx << 1) + 1;
        if (idx > max_compactiy) throw new IllegalArgumentException("index out of range");
        tree[idx] = value;
    }

    void putRight(int pareIdx, Object value) {
        int idx = (pareIdx + 1) << 1;
        if (idx > max_compactiy) throw new IllegalArgumentException("index out of range");
        tree[idx] = value;
    }

    /**
     * 获取父节点
     *
     * @param idx
     * @return
     */
    Object getParent(int idx) {
        if (idx == 0) return tree[0];
        if (idx < 0) throw new IllegalArgumentException("index not illegal");
        if (idx >= tree.length) throw new IllegalArgumentException("已经超了树的最大长度");
        if (idx > max_compactiy) throw new IllegalArgumentException("index out of range");
        return tree[(idx - 1) >> 1];
    }

    public static void main(String[] args) {
        ArrayTree tree = new ArrayTree();
        tree.putRoot("nb");
        tree.putLeft(0, "a");
        tree.putRight(0, "b");
        tree.putLeft(0, "c");
        tree.putRight(1, "d");
        System.out.println(tree);

        System.out.println("父节点===" + tree.getParent(1));
        System.out.println("父节点===" + tree.getParent(3));
    }

}
