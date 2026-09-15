package com.example.test.util;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/28 18:24
 */
public class ObjectUtils {

    /**
     * 通用的数组元素交换方法
     *
     * @param arr 要操作的数组
     * @param i   第一个元素的下标
     * @param j   第二个元素的下标
     */
    public static void swap(int[] arr, int i, int j) {
        // 健壮性校验：避免数组越界、下标相同（无意义交换）
        if (arr == null || i < 0 || j < 0 || i >= arr.length || j >= arr.length || i == j) {
            return; // 不满足条件则直接返回，避免报错
        }
        // 核心交换逻辑：临时变量中转
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
