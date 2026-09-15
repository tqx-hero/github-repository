package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 70. 爬楼梯
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 提示
 * ￼
 * 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
 * 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？ 
 * 示例 1：
 * 输入：
 * n = 2
 * 输出：
 * 2
 * 解释：
 * 有两种方法可以爬到楼顶。
 * 1. 1 阶 + 1 阶
 * 2. 2 阶
 * 示例 2：
 * 输入：
 * n = 3
 * 输出：
 * 3
 * 解释：
 * 有三种方法可以爬到楼顶。
 * 1. 1 阶 + 1 阶 + 1 阶
 * 2. 1 阶 + 2 阶
 * 3. 2 阶 + 1 阶
 *  提示：
 * • 1 <= n <= 45
 * @date 2026/5/11 18:15
 */
public class Leetcode70 {
    //斐波那契数列
    public static int climbStairs(int n) {
        if (n <= 2)
            return n;
        int left = 1, right = 2, count = 2;
        while (count < n) {
            int tmp = left + right;
            left = right;
            right = tmp;
            count++;
        }
        return right;
    }

    public static void main(String[] args) {
        System.out.println(climbStairs(4));
    }
}
