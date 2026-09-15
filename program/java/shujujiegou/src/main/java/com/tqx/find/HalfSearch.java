package com.tqx.find;

import java.util.ArrayDeque;
import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 二分查找
 * @date 2026/4/3 8:40
 */
public class HalfSearch {

    private int[] obj;
    private int length;
    private int head;
    private int tail;

    public HalfSearch(int[] obj) {
        this.length = obj.length;
        this.obj = obj;
        Arrays.parallelSort(this.obj);
        this.head = 0;
        this.tail = length - 1;
    }

    //迭代实现二分查找算法
    public int getIndex(int num) {
//        int h = this.head, t = this.tail;
        for (int h = this.head, t = this.tail; h <= t; ) {
            int mid = (h + t) >>> 1;
            if (obj[mid] == num)
                return mid;
            else if (obj[mid] > num)
                t = mid - 1;
            else
                h = mid + 1;
        }
        return -1;
    }

    //递归二分查找，但是数据量过大可能会导致方法栈溢出
    public int getIndex(int expected, int head, int tail) {
        //递归终止条件
        if (head > tail)
            return -1;
        int mid = (head + tail) >>> 1;
        if (obj[mid] == expected)
            return mid;
        else if (obj[mid] > expected)
            return getIndex(expected, head, mid - 1);
        return getIndex(expected, mid + 1, tail);
    }

    //手动栈实现
    public int getIndexByStack(int expected) {
        ArrayDeque<int[]> stack = new ArrayDeque<>();
        stack.push(new int[]{this.head, this.tail});
        while (!stack.isEmpty()) {
            int[] indexArr = stack.pop();
            int head = indexArr[0];
            int tail = indexArr[1];
            if (head > tail)
                break;
            int mid = (head + tail) >>> 1;
            if (obj[mid] == expected)
                return mid;
            else if (obj[mid] > expected)
                stack.push(new int[]{head, mid - 1});
            else
                stack.push(new int[]{mid + 1, tail});
        }
        return -1;
    }

    public static void main(String[] args) {
        int[] obj = {3, 5556, 77, 55, 22, 44, 88, 11};
        HalfSearch o = new HalfSearch(obj);
//        System.out.println(o.getIndex(77));
        System.out.println(o.getIndexByStack(10));
    }

}
