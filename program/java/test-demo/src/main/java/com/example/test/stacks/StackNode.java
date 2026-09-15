package com.example.test.stacks;

import com.example.test.tree.LinkedTree;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义含标识符的栈，标识符用来识别是否已执行
 * @date 2026/2/27 18:52
 */
public class StackNode<T> {

    public StackNode() {
    }

    public StackNode(T tree) {
        this.tree = tree;
    }

    //是否已在栈内执行
    public boolean execute = false;
    public T tree;
}
