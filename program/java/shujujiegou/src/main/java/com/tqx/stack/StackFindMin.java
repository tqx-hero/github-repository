package com.tqx.stack;

/**
 * @author Administrator
 * @version 1.0
 * @description: 栈支持能找到最大最小值
 * @date 2026/4/8 16:02
 */
public class StackFindMin {
    private static final int DEFAULT_INIT_NUM = Integer.MAX_VALUE - 1;

    private int[] arr;
    private int size;
    private int cur;
    //存放最小值在数组中的下标
    private int[] minArr;
    private int count;
    //存放最大值在数组中的下标
    private int[] maxArr;
    //最大值与最小值数组的指针
    private int minCur;
    private int maxCur;

    public StackFindMin(int size) {
        this.size = size;
        //设置index=0为哨兵节点
        this.arr = new int[size + 1];
        this.minArr = new int[size + 1];
        this.maxArr = new int[size + 1];
        arr[0] = DEFAULT_INIT_NUM;
        minArr[0] = 0;
        maxArr[0] = 0;
        this.cur = 0;
        this.minCur = 0;
        this.maxCur = 0;
        this.count = 0;
    }

    //返回当前栈内最小值的下标
    private int peekMin() {
        if (minCur == 0)
            return 0;
        return minArr[minCur];
    }

    //返回当前栈内最大值的下标
    private int peekMax() {
        if (maxCur == 0)
            return 0;
        return maxArr[maxCur];
    }

    private void pushMin(int index) {
        minArr[++minCur] = index;
    }

    private void pushMax(int index) {
        maxArr[++maxCur] = index;
    }

    public int findMin() {
        if (size == 0)
            throw new NullPointerException("栈内没有数据");
        return arr[peekMin()];
    }

    public int findMax() {
        if (size == 0)
            throw new NullPointerException("栈内没有数据");
        return arr[peekMax()];
    }


    public void push(int o) {
        if (count == size)
            throw new IndexOutOfBoundsException("栈已满");
        arr[0] = o;
        arr[++cur] = o;
        count++;
        //更新最小值下标
        int minIndex = peekMin();
        if (arr[minIndex] >= o)
            pushMin(cur);
        else
            pushMin(minIndex);

        //更新最大值下标
        int maxIndex = peekMax();
        if (arr[maxIndex] <= o)
            pushMax(cur);
        else
            pushMax(maxIndex);
    }


    public int pop() {
        if (count == 0)
            throw new NullPointerException("栈内没有数据");
        popMin();
        popMax();
        return arr[cur--];
    }

    private void popMin() {
        minCur--;
    }

    private void popMax() {
        maxCur--;
    }


    public static void main(String[] args) {
        StackFindMin stack = new StackFindMin(10);
        stack.push(20);
        System.out.println(stack.findMin());
        System.out.println(stack.findMax());
        stack.push(10);
        System.out.println(stack.findMin());
        System.out.println(stack.findMax());
        stack.push(30);
        System.out.println(stack.findMax());
        stack.pop();
        stack.pop();
        System.out.println(stack.findMin());
        System.out.println(stack.findMax());
    }


}
