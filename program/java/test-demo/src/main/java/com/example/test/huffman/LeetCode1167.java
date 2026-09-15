package com.example.test.huffman;

/**
 * @author Administrator
 * @version 1.0
 * @description: leetCode1167题
 * 有一些长度不一的木棒，每次可连接两根成一根木棒，费用是两木棒之和，问：连接所有木棒所需要的最少费用是多少？
 * 例如有sticks[2,4,3]
 * 先连2+3=5，再连5+4=9，总费用是5+9=14，这是最优解
 * 如果：4+3=7,7+2=9，总费用是7+9=16，不是最优
 * <p>
 * 就是先找到最小数两两相加，之后算出总数的过程，可以直接拼接成哈夫曼树，结果即为根节点数据
 * @date 2026/3/1 15:16
 */
public class LeetCode1167 {

    /**
     * 获取多跟木棒拼接成一根所需最少费用
     *
     * @param arr
     * @return
     */
    static int init(int[] arr) {
        HuffManTree.SmallHeap<Integer> heap = new HuffManTree.SmallHeap<>();
        for (int i = 0; i < arr.length; i++) {
            HuffManTree<Integer> tree = new HuffManTree<>(arr[i], arr[i]);
            heap.add(tree);
        }

        int sum = 0;

        while (heap.size > 1) {
            HuffManTree<Integer> left = heap.pop();
            HuffManTree<Integer> right = heap.pop();
            sum += left.weight + right.weight;
            heap.add(new HuffManTree<>(null, left, right, right.weight + left.weight));
        }
        return sum;
    }

    public static void main(String[] args) {
        System.out.println(init(new int[]{2, 4, 3}));
    }

}
