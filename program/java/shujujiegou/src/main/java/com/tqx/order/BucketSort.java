package com.tqx.order;

import java.util.Arrays;
import java.util.PriorityQueue;

/**
 * @author Administrator
 * @version 1.0
 * @description: 桶排序
 * 根据数据的最大值来定义桶的个数，遍历时将数据以偏移量的形式放入相应的桶内，即
 * 数据=10，桶count[10]=count[10]+1
 * 然后遍历桶，根据count[i]的数据，输出相应的次数，输出数据=i
 * @date 2026/4/15 23:13
 */
public class BucketSort {

    //{10,5,20,1,3,6,33}
    public static int[] sort(int[] a) {
        if (a == null || a.length <= 1)
            return a;
        //定义桶位大小为原数组长度一半
        int l = a.length;
        PriorityQueue<Integer>[] bucket = new PriorityQueue[l >>> 1];
        for (int i = 0; i < bucket.length; i++)
            bucket[i] = new PriorityQueue<>(l - 1, Integer::compareTo);
        int[] r = new int[l];
        int m = a[0], n = a[0];
        for (int i : a) {
            m = Math.max(m, i);
            n = Math.min(n, i);
        }
        //计算每个桶负责的数值区间跨度
        int f = (int) Math.ceil((m - n + 0.5) / bucket.length);
        for (int k : a)
            bucket[(k - n) / f].offer(k);
        int j = 0;
        for (PriorityQueue<Integer> h : bucket) {
            while (!h.isEmpty())
                r[j++] = h.poll();
        }
        return r;
    }

    public static void main(String[] args) {
        int[] a = {10, 5, 20, 1, 3, 6, 33};
        System.out.println(Arrays.toString(sort(a)));
//        System.out.println((int) Math.ceil((double) 30.5 / 5));
    }
}
