package com.tqx.order;

/**
 * @author Administrator
 * @version 1.0
 * @description: 希尔排序
 * @date 2026/4/6 10:02
 */
public class ShellOrder {

    public static int[] shellOrder(int[] arr) {
        if (arr == null || arr.length == 0)
            return new int[]{};
        int length = arr.length;
        int gap = length >>> 1;
        while (gap > 0) {
            for (int i = gap; i < length; i++) {
                int temp = arr[i];
                int j;
                for (j = i; j >= gap && temp < arr[j - gap]; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
            gap /= 2;
        }
        return arr;
    }

    public static void main(String[] args) {
        int[] arr = {22, 10, 30, 20, 80, 7, 50, 33};
        int[] arrs = shellOrder(arr);
        for (int i = 1; i < arrs.length; i++) {
            System.out.println(arrs[i]);
        }
    }

}
