package com.tqx.order;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 基数排序，
 * 因为数字都是由0-9这10个数构成，所以可以从0-9各准备一个桶，按照从0到9排序
 * 1、对每个数据从低位到高位大小入桶，如：341第一趟会入1号桶位，234入2号，以此类推，然后按照桶位顺序由低到高依次收集，这样就从低到高把个位数升序排好了
 * 2、接下来排十位数，还是按照1的规则入桶，出桶；
 * 3、按照2方式继续入桶、出桶；
 * 4、每当入桶时可以判断数的位数，小于这个位数的数据可以直接排好不需要拿出来，只拿不少于这个位数的数据即可
 * @date 2026/4/7 13:48
 */
public class RadixSort {

    //定义桶位
    static class Entry {
        List<Integer> nums;

        void clear() {
            nums.clear();
        }

        public Entry() {
            this.nums = new ArrayList<>();
        }
    }

    private static Entry[] initBucket() {
        Entry[] entries = new Entry[10];
        for (int i = 0; i < 10; i++)
            entries[i] = new Entry();
        return entries;
    }

    public static int[] sort(int[] arr) {
        if (arr == null || arr.length <= 1)
            return arr;
        Entry[] bucket = initBucket();
        int length = arr.length;
        //结果数组
        int[] res = new int[length];
        int start = 0;
        int remainCount = length;
        int zeroCount = 1;
        while (start < length) {
            int bucketCount = 0;
            //计算位数，个十百千万...
            int div = (int) Math.pow(10, zeroCount - 1);
            for (int i = 0; i < remainCount; i++) {
                //数据位数不够的直接入新数组，不需要再次入桶倒桶
                if (arr[i] < div) {
                    res[start++] = arr[i];
                    continue;
                }
                int index = arr[i] / div % 10;
                bucket[index].nums.add(arr[i]);
                bucketCount++;
            }
            //桶内元素数量为0时，说明顺序已经排好
            //直接跳出循环
            if (bucketCount == 0)
                break;
            remainCount = 0;
            //没排好就继续加入旧的数组，继续入桶倒桶
            for (Entry entry : bucket) {
                for (Integer num : entry.nums)
                    arr[remainCount++] = num;
                entry.clear();
            }
            zeroCount++;
        }
        return res;
    }

    public static void main(String[] args) {
        int[] arr = {22, 10, 30, 20, 80, 7, 50, 33};
        System.out.println(Arrays.toString(RadixSort.sort(arr)));
    }
}
