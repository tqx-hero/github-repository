package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 69. x 的平方根
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 提示
 * ￼
 * 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。
 * 由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
 * 注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。 
 * 示例 1：
 * 输入：
 * x = 4
 * 输出：
 * 2
 * 示例 2：
 * 输入：
 * x = 8
 * 输出：
 * 2
 * 解释：
 * 8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。
 *  提示：
 * • 0 <= x <= 231 - 1
 * @date 2026/5/10 21:23
 */
public class Leetcode69 {

    public static int mySqrt(int x) {
        if (x <= 1)
            return x;
        int right = x, left = 0;
        //left~right即为所求平方根的区间，二分查找
        while (true) {
            int mid = left + (right - left) / 2;
            int i = x / mid;
            if (i >= mid)
                return mid;
            else {
                left = i;
                right = mid;
            }
        }
    }

    public static void main(String[] args) {
        System.out.println(mySqrt(2147395599));
//        System.out.println(mySqrt(8));
    }
}
