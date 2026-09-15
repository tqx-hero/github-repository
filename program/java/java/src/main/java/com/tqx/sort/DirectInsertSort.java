package com.tqx.sort;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 直接诶插入排序
 * @date 2026/4/16 9:43
 */
public class DirectInsertSort {

    public static int[] sort(int[] a) {
        if (a == null || a.length <= 1)
            return a;
        int len = a.length;
        int[] r = new int[len + 1];
        r[1] = a[0];
        for (var i = 1; i < len; i++) {
            r[0] = a[i];
            int j;
            for (j = i; r[j] > r[0]; j--)
                r[j + 1] = r[j];
            r[j+1] = r[0];
        }
        System.arraycopy(r, 1, a, 0, len);
        return a;


    }

    public static void main(String[] args) {
        int[] a = {3, 1, 4, 1, 5, 9, 2, 6, 5};
        System.out.println(Arrays.toString(sort(a)));
    }

}
