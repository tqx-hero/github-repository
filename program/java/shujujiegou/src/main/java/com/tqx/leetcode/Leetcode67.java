package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 67. 二进制求和
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给你两个二进制字符串 a 和 b ，以二进制字符串的形式返回它们的和。 
 * 示例 1：
 * 输入:
 * a = "11", b = "1"
 * 输出："100"
 * 示例 2：
 * 输入：
 * a = "1010", b = "1011"
 * 输出："10101" 
 * 提示：
 * • 1 <= a.length, b.length <= 104
 * • a 和 b 仅由字符 '0' 或 '1' 组成
 * • 字符串如果不是 "0" ，就不含前导零
 * @date 2026/5/10 22:45
 */
public class Leetcode67 {

    //a = "1010", b = "1011"
    public static String addBinary(String a, String b) {
        StringBuilder sb = new StringBuilder();
        int al = a.length();
        int bl = b.length();
        int aPtr = al - 1, bPtr = bl - 1;
        int cf = 0;
        while (aPtr >= 0 || bPtr >= 0) {
            int result = cf;
            if (aPtr >= 0)
                result += a.charAt(aPtr--) - '0';
            if (bPtr >= 0)
                result += b.charAt(bPtr--) - '0';
            if (result == 2) {
                cf = 1;
                result = 0;
            } else if (result == 3) {
                cf = 1;
                result = 1;
            } else
                cf = 0;
            sb.append(result);
        }
        if (cf == 1)
            sb.append(cf);
        return sb.reverse().toString();
    }

    public static void main(String[] args) {
//        String a = "11", b = "1";
        String a = "1010", b = "1011";
        System.out.println(addBinary(a, b));
    }

}
