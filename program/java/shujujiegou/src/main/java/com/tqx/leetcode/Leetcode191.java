package com.tqx.leetcode;

import java.util.HashMap;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @description: 191. 位1的个数
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给定一个正整数 n，编写一个函数，获取一个正整数的二进制形式并返回其二进制表达式中 设置位 的个数（也被称为汉明重量）。 
 * 示例 1：
 * 输入：
 * n = 11
 * 输出：
 * 3
 * 解释：输入的二进制串 1011 中，共有 3 个设置位。
 * 示例 2：
 * 输入：
 * n = 128
 * 输出：
 * 1
 * 解释：输入的二进制串 10000000
 *  中，共有 1 个设置位。
 * 示例 3：
 * 输入：
 * n = 2147483645
 * 输出：
 * 30
 * 解释：输入的二进制串 1111111111111111111111111111101 中，共有 30 个设置位。 
 * 提示：
 * • 1 <= n <= 231 - 1
 * ￼ 
 * 进阶：
 * • 如果多次调用这个函数，你将如何优化你的算法？
 * @date 2026/5/11 22:59
 */
public class Leetcode191 {

//    private static final Map<Integer, Integer> cache = new HashMap<>();
//
//    public static int hammingWeight(int n) {
//        if (n == 0)
//            return 0;
//        //先从缓存拿
//        Integer i = cache.get(n);
//        if (i != null)
//            return i;
//        //缓存没有的话，则需要计算并且加入缓存
//        int res = n % 2 + hammingWeight(n >> 1);
//        cache.put(n, res);
//        return res;
//    }

//    public static int hammingWeight(int n) {
//        if (n == 0)
//            return 0;
//        return n % 2 + hammingWeight(n >> 1);
//    }

    public static int hammingWeight(int n) {
        int result = 0;
        while (n != 0) {
            result += (n & 1);
            n >>= 1;
        }
        return result;
    }

    public static void main(String[] args) {
        int n = 2147483645;
        System.out.println(hammingWeight(n));
    }
}
