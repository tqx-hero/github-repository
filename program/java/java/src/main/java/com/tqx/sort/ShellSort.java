package com.tqx.sort;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 希尔排序
 * @date 2026/4/16 10:05
 */
public class ShellSort {

    public static int[] sort(int[] a) {
        if (a == null || a.length <= 1)
            return a;
        int len = a.length;
        int gap = len / 2;
        for (int i = gap; i >= 1; i /= 2) {
            for (int j = i; j < len; j++) {
                for (int k = j; k >= i && a[k] < a[k - i]; k -= i) {
                    int tmp = a[k];
                    a[k] = a[k - i];
                    a[k - i] = tmp;
                }
            }
        }

        return a;
    }

    public static void main(String[] args) {
        int[] a = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        System.out.println(Arrays.toString(sort(a)));
    }

}
