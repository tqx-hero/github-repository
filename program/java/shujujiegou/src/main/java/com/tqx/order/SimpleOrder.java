package com.tqx.order;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 简单排序
 * @date 2026/4/7 8:27
 */
public class SimpleOrder {

    public static int[] order(int[] arr) {

        if (arr == null || arr.length == 0)
            return new int[]{};
        int length = arr.length;
        //一共进行长度-1趟排序
        for (int i = 0; i < length - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < length; j++) {
                if (arr[minIndex] > arr[j])
                    minIndex = j;
            }
            //互换最小值与i的位置
            int temp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = temp;
        }
        return arr;
    }

    public static void main(String[] args) {
        int[] arr = {22, 10, 30, 20, 80, 7, 50, 33};
        int[] arrs = SimpleOrder.order(arr);
        System.out.println(Arrays.toString(arrs));
    }
}
