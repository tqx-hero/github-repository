package com.tqx.order;

import java.util.ArrayDeque;
import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 归并排序：先分治，再合并，fork join思想
 * @date 2026/4/7 12:37
 */
public class GuiBingOrder {

    /**
     * 对两个数组进行值比较，以升序排列生成新数组
     *
     * @param arr 原数组数据
     * @param a1  存放数据所在的数组下标
     * @param a2  另一个数组下标
     * @return
     */
    private static Integer[] twoArraysUnion(int[] arr, Integer[] a1, Integer[] a2) {
        int ia1 = 0, ia2 = 0, la1 = a1.length, la2 = a2.length, ian = 0;
        Integer[] ianArr = new Integer[la1 + la2];
        while (ia1 < la1 && ia2 < la2) {
            if (arr[a1[ia1]] < arr[a2[ia2]])
                ianArr[ian++] = a1[ia1++];
            else
                ianArr[ian++] = a2[ia2++];
        }
        if (ia1 == la1 && ia2 == la2)
            return ianArr;
        if (ia1 == la1)
            System.arraycopy(a2, ia2, ianArr, ian, la2 - ia2);
        else
            System.arraycopy(a1, ia1, ianArr, ian, la1 - ia1);
        return ianArr;
    }

    public static int[] order(int[] arr) {
        if (arr == null || arr.length <= 1)
            return arr;
        int length = arr.length;
        //将要排序的数组下标分成若干下标组成的数组存放到队列中，然后对这些数据进行排序继续放入队列中，
        //循环直到队列中仅剩一个数组
        ArrayDeque<Integer[]> queue = new ArrayDeque<>();
        for (int i = 0; i < length; i++)
            queue.add(new Integer[]{i});
        int[] iArr = new int[length];
        //每次取两个数组，合并成一个数组，直到队列中只剩下一个数组
        while (queue.size() > 1)
            queue.add(twoArraysUnion(arr, queue.poll(), queue.poll()));
        Integer[] resultIndex = queue.poll();
        for (int i = 0; i < length; i++)
            iArr[i] = arr[resultIndex[i]];
        return iArr;
    }

    public static void main(String[] args) {
        int[] a1 = {20, 10, 30, 22, 40, 100, 70, 50};
//        int[] a1 = {20, 10, 30, 23};
//        int[] a2 = {1, 2, 3, 4, 6, 7};
        System.out.println(Arrays.toString(GuiBingOrder.order(a1)));
    }

}
