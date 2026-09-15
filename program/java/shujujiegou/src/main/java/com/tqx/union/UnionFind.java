package com.tqx.union;

import java.util.Arrays;
import java.util.concurrent.atomic.AtomicLong;

/**
 * @author Administrator
 * @version 1.0
 * @description: 交并集查找
 * @date 2026/4/16 15:22
 */
public class UnionFind {
    private static final int ROOT = -1;
    private UNode[] root;
    private int size;
    //根节点集合
    private int[] parent;
    //设置唯一标识
    private static final AtomicLong UUID;

    static {
        UUID = new AtomicLong(0L);
    }

    private static class UNode {
        int rank;
        long uuid;
        int key;
        UNode parent;

        @Override
        public String toString() {
            return "UNode{" +
                    "key=" + key +
                    ", rank=" + rank +
                    ", uuid=" + uuid +
                    ", parent=" + parent +
                    '}';
        }

        public UNode(int key) {
            this.key = key;
            uuid = UUID.getAndIncrement();
            rank = 1;
        }

        public UNode parent(UNode parent) {
            this.parent = parent;
            return this;
        }
    }

    @Override
    public String toString() {
        return "UnionFind{" +
                "parent=" + Arrays.toString(parent) +
                ", root=" + Arrays.toString(root) +
                ", size=" + size +
                '}';
    }

    public UnionFind(int[] arr) {
        this(arr.length);
        init(arr);
    }

    private void init(int[] arr) {
        for (int i = 0; i < size; i++) {
            root[i] = new UNode(arr[i]);
            parent[i] = ROOT;
        }
    }

    public UnionFind(int size) {
        this.size = size;
        root = new UNode[size];
        parent = new int[size];
    }

    //找到根节点，并返回过来，同时回溯更新路径上的
    //所有节点的parent
    private int find(int x) {
        if (parent[x] == ROOT)
            return x;
        return parent[x] = find(parent[x]);
    }

    //连接根节点
    private void union(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy)
            return;
        if (root[fx].rank >= root[fy].rank)
            parent[fy] = fx;
        else
            parent[fx] = fy;
    }

    public void setParent(int par, int child) {
        root[child].parent = root[par];
        root[par].rank += root[child].rank;
        union(par, child);
    }

    public static void main(String[] args) {
        int[] a = {1, 2, 3, 4, 5, 6, 7};
        UnionFind u = new UnionFind(a);
        u.setParent(3, 4);
        u.setParent(5, 6);
        u.setParent(3, 5);
        System.out.println(u);
        u.setParent(0, 3);
        System.out.println(u);
        u.setParent(6, 1);
        System.out.println(u);
    }
}
