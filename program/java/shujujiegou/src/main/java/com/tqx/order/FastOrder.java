package com.tqx.order;

import java.util.ArrayDeque;
import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 快速排序:挖坑法
 * 每次取第一个位置数据，放到哨兵位置，分别在始末位置与哨兵位置数据作比较，末尾小的往前挪到low位置，找不到就继续--往前移动找，直到high =low
 * 挪完以后high位置空了，low开始与哨兵位置比较，小的就++往后移动，直到摘到大的往high位置移过去，或者直到low与high指针重叠
 * 完成这一次排序后，两个指针必重叠，以该位置为界分成前后两部分[0,low-1],[low+1,high]，分别对这两部分继续递归执行以上操作
 * 一直到区间内数据只剩下一个即可。
 * 注意：如果数据量比较大，递归的算法可能会使方法栈累加超出导致栈溢出OOM
 * 所以实际开发中最好还是推荐以手动栈来代替递归。
 * @date 2026/4/6 16:15
 */
public class FastOrder {

    public static int[] quickSort(int[] arr) {
        if (arr == null || arr.length == 0)
            return new int[]{};
        int length = arr.length;
        int[] arrs = new int[length + 1];
        System.arraycopy(arr, 0, arrs, 1, length);
        ArrayDeque<Integer[]> stack = new ArrayDeque<>();
        //将起始位置low与末尾high的下标打包成数组压入栈内
        stack.push(new Integer[]{1, length});
        while (!stack.isEmpty()) {
            Integer[] indexArr = stack.pop();
            //得到始末位置的坐标
            int start = indexArr[0], end = indexArr[1];
            int low = start, high = end;
            //将初始位置的数据放入哨兵位置
            arrs[0] = arrs[low];
            for (; low < high; ) {
                for (; high > low && arrs[high] >= arrs[0]; high--) ;
                //找到比当前哨兵位置数据更小的，放入low位置
                arrs[low] = arrs[high];
                for (; low < high && arrs[low] <= arrs[0]; low++) ;
                arrs[high] = arrs[low];
            }
            //哨兵位置的数据放到遍历完成的空位置
            arrs[low] = arrs[0];
            //查看区间内剩余个数，大于1的区间继续将始末位置下标压入栈内迭代
            if (end > low + 1)
                stack.push(new Integer[]{low + 1, end});
            if (start < low - 1)
                stack.push(new Integer[]{start, low - 1});
        }
        System.arraycopy(arrs, 1, arr, 0, length);
        return arr;
    }

    public static void main(String[] args) {
        int[] arr = {22, 10, 30, 20, 80, 7, 50, 33};
        int[] arrs = quickSort(arr);
        System.out.println(Arrays.toString(arrs));
    }
}
