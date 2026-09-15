package com.tqx.leetcode;

import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 给你一个字符串 s，找到 s 中最长的 回文 子串。
 * <p>
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * 输入：s = "babad"
 * 输出："bab"
 * 解释："aba" 同样是符合题意的答案。
 * 示例 2：
 * <p>
 * 输入：s = "cbbd"
 * 输出："bb"
 * @date 2026/3/27 8:39
 */
public class Leetcode05 {
    //需要遍历判断字符两边是否相同
    public static String longestPalindrome(String s) {
        if (Objects.isNull(s))
            return null;
        if (s.length() == 1)
            return s;
        char[] array = s.toCharArray();
        int len = 0, begin = 0;
        for (int left = 0; left < s.length() - 1; left++) {
            for (int right = left + 1; right < s.length(); right++) {
                if (right - left + 1 > len && isHuiwen(array, left, right)) {
                    len = right - left + 1;
                    begin = left;
                }
            }
        }
        if (len == 0)
            return String.valueOf(s.charAt(0));
        return s.substring(begin, begin + len);
    }

    static boolean isHuiwen(char[] array, int begin, int end) {
        for (; begin < end; begin++, end--) {
            if (!(array[begin] == array[end]))
                return false;
        }
        return true;
    }


    public static void main(String[] args) {
//        System.out.println(longestPalindrome("a"));
//        System.out.println(longestPalindrome("bb"));
//        System.out.println(longestPalindrome("abbcccba"));
//        System.out.println(longestPalindrome("ccc"));
//        System.out.println(longestPalindrome("cbbd"));
//        System.out.println(longestPalindrome("babad"));
//        System.out.println(longestPalindrome("abbcccba"));
        System.out.println(longestPalindrome("abcda"));
    }
}
