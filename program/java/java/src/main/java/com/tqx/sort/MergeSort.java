package com.tqx.sort;

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

/**
 * @author Administrator
 * @version 1.0
 * @description: 归并排序
 * @date 2026/4/16 11:35
 */
public class MergeSort {

    public static int[] sort(int[] a) {
        if (a == null || a.length <= 1)
            return a;
        int len = a.length;
        Queue<Integer[]> queue = new ArrayDeque<>();
        int[] r = new int[len];
        //初始化合并单元
        for (int i = 0; i < len; i++)
            queue.offer(new Integer[]{i});

        while (queue.size() > 1)
            queue.offer(merge(queue.poll(), queue.poll(), a));
        Integer[] s = queue.poll();
        for (int i = 0; i < s.length; i++)
            r[i] = a[s[i]];
        return r;
    }

    private static Integer[] merge(Integer[] a, Integer[] b, int[] data) {
        if (a == null || a.length == 0)
            return b;
        if (b == null || b.length == 0)
            return a;
        int i = 0, j = 0, k = 0, m = a.length, n = b.length;
        Integer[] r = new Integer[m + n];
        while (i < m && j < n)
            r[k++] = data[a[i]] <= data[b[j]] ? a[i++] : b[j++];
        while (i < m)
            r[k++] = a[i++];
        while (j < n)
            r[k++] = b[j++];
        return r;
    }

    public static void main(String[] args) {
        int[] a = {3, 1, 4, 1, 5, 9, 2, 6};
        System.out.println(Arrays.toString(sort(a)));
    }
}
