package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 125. 验证回文串
 * 简单
 * 相关标签
 * premium lock icon
 * 相关企业
 * 如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个 回文串 。
 * <p>
 * 字母和数字都属于字母数字字符。
 * <p>
 * 给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false 。
 * <p>
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * 输入: s = "A man, a plan, a canal: Panama"
 * 输出：true
 * 解释："amanaplanacanalpanama" 是回文串。
 * 示例 2：
 * <p>
 * 输入：s = "race a car"
 * 输出：false
 * 解释："raceacar" 不是回文串。
 * 示例 3：
 * <p>
 * 输入：s = " "
 * 输出：true
 * 解释：在移除非字母数字字符之后，s 是一个空字符串 "" 。
 * 由于空字符串正着反着读都一样，所以是回文串。
 * <p>
 * <p>
 * 提示：
 * <p>
 * 1 <= s.length <= 2 * 105
 * s 仅由可打印的 ASCII 字符组成
 * @date 2026/5/13 18:15
 */
public class Leetcode125 {

    //转化有效字符
    //数字返回原ASCII码，字母全部转成大写
    private static char getChar(char c) {
        if ((c >= '0' && c <= '9') || ((c &= 0xdf) >= 'A' && c <= 'Z')) {
            return c;
        } else
            return 0;
    }

    public static boolean isPalindrome(String s) {
        int length = s.length();
        if (length == 1)
            return true;
        int left = 0, right = length - 1;
        for (; left <= right; ) {
            char c = 0;
            //如果不符合条件，移动左指针直到找到符合条件的字符
            for (; left <= right && (c = getChar(s.charAt(left))) == 0; left++) ;
            //找right
            char r = 0;
            for (; left <= right && (r = getChar(s.charAt(right))) == 0; right--) ;
            if (c != r)
                return false;
            left++;
            right--;
        }
        return true;
    }

    public static void main(String[] args) {
//        String s = "race a car";
//        String s = "  ";
//        String s = "A man, a plan, a canal: Panama";
        String s = "a.";
        System.out.println(isPalindrome(s));
    }
}
