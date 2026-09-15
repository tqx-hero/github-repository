package com.example.test.btree;

import java.util.ArrayList;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个B-Tree
 * @date 2026/3/2 15:20
 */
public class BTree {

    int M = 5;  //B树的阶数
    int i = 0;      //当前节点key的数量
    int[] keys; //当前节点的key集合
    BTree[] children; //当前节点下子节点
    boolean isLeaf = false; //是否是叶子结点

    public BTree() {
        this.keys = new int[M - 1];
        this.children = new BTree[M - 1];
    }

    public BTree(int m) {
        M = m;
        this.keys = new int[M - 1];
        this.children = new BTree[M - 1];
    }


    public static void main(String[] args) {
        Integer i1 = 128;
        Integer i = 128;
        System.out.println(i1 == i);  //返回false

    }

}
