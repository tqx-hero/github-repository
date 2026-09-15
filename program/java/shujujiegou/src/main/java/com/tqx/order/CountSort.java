package com.tqx.order;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 计数排序
 * 桶排序的延伸，适用于数量有限且极值差不大，数据较平均的场景
 * @date 2026/4/15 22:41
 */
public class CountSort {

    //{10,5,20,1,3,6,33}

    public static int[] sort(int[] a) {
        if (a == null || a.length <= 1)
            return a;
        //查找极值
        int max = a[0], min = a[0];
        for (int i : a) {
            max = Math.max(max, i);
            min = Math.min(min, i);
        }
        //定义count数组，记录数据出现次数
        int[] count = new int[max - min + 1];
        int[] offset = new int[max - min + 1];
        int[] r = new int[a.length];
        //统计数据出现次数
        for (int i : a)
            count[i - min]++;
        //计算每个数据在排序后数组中的偏移量，
        //如果有多个相同数据，偏移量为最后那个数据的,所以在最后的编排过程需要倒序来遍历
        offset[0] = count[0];
        for (int k = 1; k < count.length; k++)
            offset[k] = offset[k - 1] + count[k];
        //倒序遍历原数组，根据偏移量填入新数组
        for (int i = a.length - 1; i >= 0; i--)
            r[(offset[a[i] - min]--) - 1] = a[i];
        return r;
    }

    public static void main(String[] args) {
        int[] a = {10, 5, 20, 1, 3, 6, 33};
        System.out.println(Arrays.toString(sort(a)));
    }

}
