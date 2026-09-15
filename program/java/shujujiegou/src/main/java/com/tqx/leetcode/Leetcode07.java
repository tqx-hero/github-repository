package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 整数反转
 * 给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
 * <p>
 * 如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1] ，就返回 0。
 * <p>
 * 假设环境不允许存储 64 位整数（有符号或无符号）。
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * 输入：x = 123
 * 输出：321
 * 示例 2：
 * <p>
 * 输入：x = -123
 * 输出：-321
 * 示例 3：
 * <p>
 * 输入：x = 120
 * 输出：21
 * 示例 4：
 * <p>
 * 输入：x = 0
 * 输出：0
 * <p>
 * <p>
 * 提示：
 * <p>
 * -231 <= x <= 231 - 1
 * @date 2026/3/31 21:30
 */
public class Leetcode07 {

    public static int reverse(int x) {
        if (x == 0) return 0;
        String str = String.valueOf(x);
        if (x < 0)
            str = str.substring(1);
        StringBuilder builder = new StringBuilder(str);
        String newStr = builder.reverse().toString();
        String resStr = x < 0 ? "-" + newStr : newStr;
        Long l = Long.valueOf(resStr);
        if (l > Integer.MAX_VALUE-1 || l < Integer.MIN_VALUE)
            return 0;
        return Integer.parseInt(resStr);

    }

    public static void main(String[] args) {
        System.out.println(reverse(Integer.MIN_VALUE));

    }
}
