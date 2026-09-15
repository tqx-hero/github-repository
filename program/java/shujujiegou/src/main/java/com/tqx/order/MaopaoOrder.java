package com.tqx.order;

/**
 * @author Administrator
 * @version 1.0
 * @description: 冒泡排序
 * @date 2026/4/6 11:57
 */
public class MaopaoOrder {

    public static int[] maopao(int[] arr) {
        if (arr == null || arr.length == 0)
            return new int[]{};
        int n = arr.length;
        //表示在排序是是否没有存在过数据位置调换
        //如果有没有数据交换，说明已经排好序了
        //此时可直接返回，不再需要遍历
        boolean ordered = false;
        //需要i趟比较
        for (int i = 1; i <= n - 1 && !ordered; i++) {
            ordered = true;
            //每趟比较n-i次
            for (int j = 0; j < n - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    arr[j] = arr[j] ^ arr[j + 1];
                    arr[j + 1] = arr[j] ^ arr[j + 1];
                    arr[j] = arr[j] ^ arr[j + 1];
                    ordered = false;
                }
            }
        }
        return arr;
    }

    public static void main(String[] args) {
        int[] arr = {22, 10, 30, 20, 80, 7, 50, 33};
        int[] arrs = maopao(arr);
        for (int i = 0; i < arrs.length; i++) {
            System.out.println(arrs[i]);
        }
    }
}
