package com.tqx.tree;

import java.util.ArrayDeque;

/**
 * @author Administrator
 * @version 1.0
 * @description: 手搓AVL树-平衡二叉树
 * @date 2026/4/3 18:26
 */
public class AVLTree {

    //平衡树失衡类型
    private static final String IMBALANCE_LL = "LL";
    private static final String IMBALANCE_RR = "RR";
    private static final String IMBALANCE_LR = "LR";
    private static final String IMBALANCE_RL = "RL";
    private AVLTreeNode root;

    static class AVLTreeNode {
        int value;
        AVLTreeNode left;
        AVLTreeNode right;
        //计算的树高度，后续旋转会频繁更新
        int height;

        @Override
        public String toString() {
            return "AVLTreeNode{" +
                    "height=" + height +
                    ", value=" + value +
                    ", left=" + left +
                    ", right=" + right +
                    '}';
        }


        public AVLTreeNode(int value) {
            this.value = value;
        }
    }

    //添加元素，同时保证平衡
    private void addElement(AVLTreeNode root, int value) {
        if (root == null)
            return;
        AVLTreeNode currentNode = root;
        ArrayDeque<AVLTreeNode> stack = new ArrayDeque<>();
        while (currentNode != null) {
            int cu = currentNode.value;
            if (value == cu)
                return;
            stack.push(currentNode);
            if (value < cu)
                currentNode = currentNode.left;
            else
                currentNode = currentNode.right;
        }
        AVLTreeNode newNode = new AVLTreeNode(value);
        //弹出栈顶(父节点)，插入数据
        AVLTreeNode prevNode = stack.poll();
        int parentValue = prevNode.value;
        if (value < parentValue)
            prevNode.left = newNode;
        else
            prevNode.right = newNode;
        //更新路过的节点的高度height
        updateHeight(prevNode);
        while (!stack.isEmpty()) {
            AVLTreeNode treeNode = stack.pop();
            updateHeight(treeNode);
            //BF绝对值已经大于1，需要对树进行翻转
            //分情况判断： LL 、RR、LR、RL
            int bf = getBalanceFactor(treeNode);
            if (Math.abs(bf) > 1)
                balanceTree(treeNode, getImBalanceType(treeNode, bf));

        }
    }

    private String getImBalanceType(AVLTreeNode treeNode, int bf) {
        AVLTreeNode left = treeNode.left;
        AVLTreeNode right = treeNode.right;
        if (bf > 1 && getBalanceFactor(left) >= 0)
            return IMBALANCE_LL;
        else if (bf > 1 && getBalanceFactor(left) < 0)
            return IMBALANCE_LR;
        else if (bf < -1 && getBalanceFactor(right) < 0)
            return IMBALANCE_RR;
        else if (bf < -1 && getBalanceFactor(right) >= 0)
            return IMBALANCE_RL;
        return "";
    }

    //LL型 : c <- b <- a 翻转后 ：  c <- b -> a ，只修改了a与b的位置，所以
    //需要修改这两个的指针以及高度，别忘了还有b的右孩子节点给a
    private void reverseTreeByLl(AVLTreeNode tree) {
        AVLTreeNode middleNode = tree.left;
        AVLTreeNode rightNode = middleNode.right;
        middleNode.right = tree;
        tree.left = rightNode;
        updateHeight(tree, middleNode);
        update(tree, middleNode);
    }

    //如果当前节点为根节点，更新根节点
    private void update(AVLTreeNode currentNode, AVLTreeNode newNode) {
        if (this.root.value != currentNode.value)
            return;
        this.root = newNode;
    }

    //LR型 :  b <- (right) c <- (left) a
    //此时a > c >b
    //需要将c移动到a位置， 结果为 ： b <- (left) c (right)-> a
    //同时需要将c的左子结点挪到b成为右子孩子节点
    //c的右子节点挪到a成为a的左孩子结点
    private void reverseTreeByLr(AVLTreeNode tree) {
        AVLTreeNode minNode = tree.left;
        AVLTreeNode middleNode = minNode.right;
        AVLTreeNode left = middleNode.left;
        AVLTreeNode right = middleNode.right;
        //开始旋转
        middleNode.left = minNode;
        middleNode.right = tree;
        minNode.right = left;
        tree.left = right;
        //更新高度，从当前子节点开始，顺序为 : a/b/c
        updateHeight(tree, minNode, middleNode);
        //如果a是根节点，替换
        update(tree, middleNode);
    }

    //RR型 : 逆时针旋转， a->b->c   变为 ：  a<- b ->c，并且把b的left挂到a的right
    private void reverseTreeByRr(AVLTreeNode tree) {
        AVLTreeNode middle = tree.right;
        AVLTreeNode left = middle.left;
        middle.left = tree;
        tree.right = left;
        //计算并更新middle与tree的值
        updateHeight(tree, middle);
        update(tree, middle);
    }

//    private void updateHeight(AVLTreeNode node) {
//        if (node == null)
//            return;
//        node.height = 1 + Math.max(height(node.left), height(node.right));
//    }

    //批量更新高度，注意更新顺序，由前到后顺序排列
    private void updateHeight(AVLTreeNode... tree) {
        if (tree == null)
            return;
        for (AVLTreeNode node : tree) {
            node.height = 1 + Math.max(height(node.left), height(node.right));
        }
    }

    //RL型 : a-> (R)b ->c(L) ,旋转后： a <- c -> b ,
    //同时需考虑c有子树的情况，这样根据中序排列规则，分别将左子树
    //挪到a的右孩子节点
    //右子树挪到b的左孩子结点
    //完成后计算树的高度，高度必须从abc这三个节点的高度最低的开始计算
    //顺序为  : a b c
    private void reverseTreeByRl(AVLTreeNode tree) {
        AVLTreeNode maxNode = tree.right;
        AVLTreeNode middleNode = maxNode.left;
        AVLTreeNode left = middleNode.left;
        AVLTreeNode right = middleNode.right;
        //开始旋转
        middleNode.left = tree;
        middleNode.right = maxNode;
        tree.right = left;
        maxNode.left = right;
        //计算更新高度
        updateHeight(tree, maxNode, middleNode);
        //判断旋转前是否为根节点，是的话需要重新设置根节点为c
        update(tree, middleNode);
    }

    //判断树失衡类型
    //根据类型翻转树
    private void balanceTree(AVLTreeNode tree, String balanceType) {
        switch (balanceType) {
            case IMBALANCE_LL:
                reverseTreeByLl(tree);
                break;
            case IMBALANCE_LR:
                reverseTreeByLr(tree);
                break;
            case IMBALANCE_RR:
                reverseTreeByRr(tree);
                break;
            case IMBALANCE_RL:
                reverseTreeByRl(tree);
                break;
        }
    }

    //计算节点的平衡因子BF = 左子树高度-右子树高度
    private int getBalanceFactor(AVLTreeNode node) {
        if (node == null)
            return 0;
        return height(node.left) - height(node.right);
    }

    private int height(AVLTreeNode node) {
        return node == null ? 0 : node.height;
    }


    public AVLTreeNode add(int[] arr) {
        // {1,2,3}
        if (arr == null || arr.length == 0)
            return null;
        this.root = new AVLTreeNode(arr[0]);
        for (int i = 1; i < arr.length; i++) {
            addElement(this.root, arr[i]);
        }
        return this.root;
    }

    public static void main(String[] args) {
//        int[] arr = {1, 2, 3};
        int[] arr = {16, 3, 7, 11, 9, 26, 18, 14, 15};
//        int[] arr = {1, 3, 2};
        AVLTree avlTree = new AVLTree();
        System.out.println(avlTree.add(arr));
    }

}
