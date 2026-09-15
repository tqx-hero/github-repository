package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。
 * 回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
 * • 例如，121 是回文，而 123 不是。 
 * 示例 1：
 * 输入：
 * x = 121
 * 输出：
 * true
 * 示例 2：
 * 输入：
 * x = -121
 * 输出：
 * false
 * 解释：
 * 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
 * 示例 3：
 * 输入：
 * x = 10
 * 输出：
 * false
 * 解释：
 * 从右向左读, 为 01 。因此它不是一个回文数。
 * @date 2026/4/1 0:25
 */
public class Leetcode09 {

    public static boolean isPalindrome(int x) {
        String s = String.valueOf(x);
        int length = s.length();
        if (length == 1)
            return true;
        String str1 = "";
        StringBuilder sb = new StringBuilder();
        int middleIdx = (length - 1) >> 1;
        if (length % 2 == 1) {
            str1 = s.substring(0, middleIdx);
        } else {
            str1 = s.substring(0, middleIdx + 1);
        }
        sb.append(s.substring(middleIdx + 1));
        return sb.reverse().toString().equals(str1);
    }

    public static void main(String[] args) {
        String str = "1234";
//        int middleIdx = (str.length() - 1) >> 1;
//        System.out.println(str.substring(0, middleIdx + 1));
//        System.out.println(str.substring(middleIdx + 1));
        System.out.println(isPalindrome(123321));
    }

}
