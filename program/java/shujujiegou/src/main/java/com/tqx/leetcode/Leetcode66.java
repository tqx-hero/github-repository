package com.tqx.leetcode;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 66. 加一
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给定一个表示 大整数 的整数数组 digits，其中 digits[i] 是整数的第 i 位数字。这些数字按从左到右，从最高位到最低位排列。这个大整数不包含任何前导 0。
 * 将大整数加 1，并返回结果的数字数组。 
 * 示例 1：
 * 输入：
 * digits = [1,2,3]
 * 输出：
 * [1,2,4]
 * 解释：
 * 输入数组表示数字 123。
 * 加 1 后得到 123 + 1 = 124。
 * 因此，结果应该是 [1,2,4]。
 * 示例 2：
 * 输入：
 * digits = [4,3,2,1]
 * 输出：
 * [4,3,2,2]
 * 解释：
 * 输入数组表示数字 4321。
 * 加 1 后得到 4321 + 1 = 4322。
 * 因此，结果应该是 [4,3,2,2]。
 * 示例 3：
 * 输入：
 * digits = [9]
 * 输出：
 * [1,0]
 * 解释：
 * 输入数组表示数字 9。
 * 加 1 得到了 9 + 1 = 10。
 * 因此，结果应该是 [1,0]。
 *  提示：
 * • 1 <= digits.length <= 100
 * • 0 <= digits[i] <= 9
 * • digits 不包含任何前导 0。
 * @date 2026/5/11 17:37
 */
public class Leetcode66 {
    //从后往前每个元素+1
    //当结果超过9时，元素置0且进位cf=1，继续往前迭代
    //当结果<=9，cf置0，退出循环
    //紧接着判断cf是否为1
    //为0直接返回原数组
    //为1需要创建新数组，且新数组首元素为1，直接返回新数组即可
    public static int[] plusOne(int[] digits) {
        int length = digits.length;
        int cf = 1, i = length - 1;
        while (cf == 1 && i >= 0) {
            digits[i] += cf;
            //该位加完后超过9，置0进1，继续迭代
            if (digits[i] > 9) {
                cf = 1;
                digits[i--] = 0;
            } else
                cf = 0;
        }
        if (cf == 0)
            return digits;
            //如果加完以后还有进位，说明原数组中全是999
            //创建新数组，首位置0
        else {
            int[] ints = new int[length + 1];
            ints[0] = 1;
            return ints;
        }
    }

    public static void main(String[] args) {
//        int [] digits = {4,3,2,1};
        int [] digits = {9,9,9,9};
        System.out.println(Arrays.toString(plusOne(digits)));
    }
}
