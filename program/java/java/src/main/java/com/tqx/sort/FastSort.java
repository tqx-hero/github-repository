package com.tqx.sort;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

/**
 * @author Administrator
 * @version 1.0
 * @description: 快速排序，三数中值法
 * @date 2026/4/16 12:21
 */
public class FastSort {

    public static int[] sort(int[] a) {
        if (a == null || a.length <= 1)
            return a;
        ArrayDeque<Integer[]> stack = new ArrayDeque<>();
        stack.push(new Integer[]{0, a.length - 1});
        while (!stack.isEmpty()) {
            Integer[] ia = stack.pop();
            int lt = ia[1], tail = lt - 1, head = ia[0];
            swap(getMidIndex(head, lt, a), lt, a);
            while (tail >= head) {
                for (; a[head] < a[lt]; head++) ;
                for (; a[tail] > a[lt]; tail--) ;
                if (tail >= head)
                    swap(head++, tail--, a);
            }
            swap(lt, ++tail, a);
            //以tail为界分割左右两个子数组，继续压栈排序
            if (tail - 1 > ia[0])
                stack.push(new Integer[]{ia[0], tail - 1});
            if (tail + 1 < lt)
                stack.push(new Integer[]{tail + 1, lt});
        }
        return a;
    }

    private static int getMidIndex(int begin, int last, int[] a) {
        ArrayList<Integer> list = new ArrayList<>(3);
        int mid = begin + (last - begin) / 2;
        list.add(begin);
        list.add(last);
        list.add(mid);
        list.sort(Comparator.comparingInt(y -> a[y]));
        return list.get(1);
    }

    private static void swap(int i, int j, int[] a) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    public static void main(String[] args) {
//        int[] a = {3, 1, 4, 1, 5, 9, 2, 6, 5};
        int[] a = {3, 1, 4, 1, 5, 9, 2, 6, 5};
        System.out.println(Arrays.toString(sort(a)));
    }
}
