package com.tqx.leetcode;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 28. 找出字符串中第一个匹配项的下标
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。 
 * 示例 1：
 * 输入：
 * haystack = "sadbutsad", needle = "sad"
 * 输出：
 * 0
 * 解释：
 * "sad" 在下标 0 和 6 处匹配。
 * 第一个匹配项的下标是 0 ，所以返回 0 。
 * 示例 2：
 * 输入：
 * haystack = "leetcode", needle = "leeto"
 * 输出：
 * -1
 * 解释：
 * "leeto" 没有在 "leetcode" 中出现，所以返回 -1 。
 *  提示：
 * • 1 <= haystack.length, needle.length <= 104
 * • haystack 和 needle 仅由小写英文字符组成
 * @date 2026/5/10 11:16
 */
public class Leetcode28 {

    //haystack = "sadbutsad", needle = "sad"
    public static int strStr(String haystack, String needle) {
        int nl = needle.length();
        int hl = haystack.length();
        if (nl > hl)
            return -1;
        //kmp算法求出next数组
        int[] next = getNext(needle, nl);
        int j = 0, i = 0;
        for (; i < hl && j < nl; ) {
            //相等则指针同时向后挪
            if (haystack.charAt(i) == needle.charAt(j)) {
                j++;
                i++;
            } else if (j == 0) {
                i++;
            } else {
                j = next[j];
            }
        }
        if (j == nl)
            return i - nl;
        return -1;
    }

    public static int[] getNext(String str, int len) {
        int[] next = new int[len];
        for (int i = 2; i < len; i++) {
            int j = next[i - 1];
            char c = str.charAt(i - 1);
            for (; j != 0 && c != str.charAt(j); j = next[j]) ;
            next[i] = c == str.charAt(j) ? j + 1 : 0;
        }
        return next;
    }

    public static void main(String[] args) {
//        System.out.println(Arrays.toString(getNext("abcabc", 6)));
//        String haystack = "mississippi", needle = "issipi";
        String haystack = "mississippi", needle = "ppi";
        System.out.println(strStr(haystack, needle));
    }


}
