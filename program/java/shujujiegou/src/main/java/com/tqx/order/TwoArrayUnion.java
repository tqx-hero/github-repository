package com.tqx.order;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 两个数组合并升序
 * 前提要求是这两个数组已经是升序
 * @date 2026/4/7 11:44
 */
public class TwoArrayUnion {

    public static int[] order(int[] a, int[] b) {
        if (a == null || a.length == 0)
            return b;
        if (b == null || b.length == 0)
            return a;
        int la = a.length;
        int lb = b.length;
        int ia = 0, ib = 0, in = 0;
        int[] newArr = new int[la + lb];
        //合并，双指针分别指向两个数组下标
        while (ia < la && ib < lb) {
            if (a[ia] < b[ib])
                newArr[in++] = a[ia++];
            else
                newArr[in++] = b[ib++];
        }
        //查看剩余的那个数组是哪个，然后把这些数全部添加到新数组的尾部
        if (la > lb)
            for (; ia < la; ia++)
                newArr[in++] = a[ia];

        else
            for (; ib < lb; ib++)
                newArr[in++] = b[ib];


        return newArr;
    }

    public static void main(String[] args) {
        int[] a1 = {1, 2, 3, 4, 6};
        int[] a2 = {1, 2, 3, 4, 6, 7};
        System.out.println(Arrays.toString(TwoArrayUnion.order(a1, a2)));
    }

}
