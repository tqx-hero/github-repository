package com.example.test.tree;

import com.example.test.stacks.ArrayStackDemo;
import com.example.test.stacks.StackNode;

import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 用栈实现树的遍历
 * <p>
 * * A
 * * | \
 * * B   C
 * * |  |  \
 * * D  G   H
 * * | \
 * * E   F
 * @date 2026/2/27 16:46
 */
public class TreeListByStack {

    static void itertor(LinkedTree<Object> tree) {
        //定义一个栈
        ArrayStackDemo stack = new ArrayStackDemo();
        //将树放入栈内
        stack.push(tree);
        //遍历栈顶
        while (Objects.nonNull(stack.peek())) {
            LinkedTree<Object> object = (LinkedTree<Object>) stack.pop();
            System.out.println(object.getData().toString());
            if (Objects.nonNull(object.getRight())) {
                stack.push(object.getRight());
            }
            if (Objects.nonNull(object.getLeft())) {
                stack.push(object.getLeft());
            }
        }
    }


    /**
     * 中序遍历
     *
     * @param tree
     */
    static void itertorMiddle(LinkedTree<Object> tree) {
        //定义一个栈
        ArrayStackDemo stack = new ArrayStackDemo();
//        stack.push(tree);
        //遍历栈顶
        while (Objects.nonNull(stack.peek()) || Objects.nonNull(tree)) {
            while (Objects.nonNull(tree)) {
                stack.push(tree);
                tree = tree.getLeft();
            }
            tree = (LinkedTree<Object>) stack.pop();
            System.out.println(tree.getData().toString());
            tree = tree.getRight();
        }
    }


    /**
     * 逆序遍历
     *
     * @param tree
     */
    static void itertorLast(LinkedTree<Object> tree) {
        //定义一个栈
        ArrayStackDemo stack = new ArrayStackDemo();
        StackNode<LinkedTree<Object>> stackNode = new StackNode<>(tree);
        stack.push(stackNode);
        //遍历栈顶
        while (Objects.nonNull(stack.peek())) {
            StackNode<LinkedTree<Object>> info = (StackNode<LinkedTree<Object>>) stack.pop();
            if (info.execute) {
                System.out.println(info.tree.getData());
            } else {
                info.execute = true;
                stack.push(info);
                if (Objects.nonNull(info.tree.getRight())) {
                    stack.push(new StackNode<>(info.tree.getRight()));
                }
                if (Objects.nonNull(info.tree.getLeft())) {
                    stack.push(new StackNode<>(info.tree.getLeft()));
                }
            }
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
//        TreeListByStack.itertor(tree);
        TreeListByStack.itertorMiddle(tree);
//        TreeListByStack.itertorLast(tree);
    }


}
