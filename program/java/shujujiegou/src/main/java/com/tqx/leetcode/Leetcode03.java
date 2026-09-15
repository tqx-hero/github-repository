package com.tqx.leetcode;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。
 * <p>
 * <p>
 * <p>
 * 示例 1:
 * <p>
 * 输入: s = "abcabcbb"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。
 * 示例 2:
 * <p>
 * 输入: s = "bbbbb"
 * 输出: 1
 * 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
 * 示例 3:
 * <p>
 * 输入: s = "pwwkew"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
 * 请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
 * @date 2026/3/26 20:06
 */
public class Leetcode03 {

    public static int lengthOfLongestSubstring(String s) {
        HashSet<Character> set = new HashSet<>();
        int total = 0;
        for (int left = 0, right = 0; right < s.length(); right++) {
            //判断集合中有没有该字符，没有则添加

            //有相同的，移动左指针，直到没有相同的为止
            while (set.contains(s.charAt(right)))
                set.remove(s.charAt(left++));
            if (!set.contains(s.charAt(right)))
                set.add(s.charAt(right));

            total = Math.max(right - left + 1, total);
        }
        return total;
    }

    public static void main(String[] args) {
//        System.out.println(lengthOfLongestSubstring("cdd"));
//        System.out.println(lengthOfLongestSubstring("abcabcbb"));
//        System.out.println(lengthOfLongestSubstring("dvdf"));
//        System.out.println(lengthOfLongestSubstring("pwwkew"));
//        System.out.println(lengthOfLongestSubstring("abba"));
//        System.out.println(ss("dedv"));
        System.out.println(lengthOfLongestSubstring("aab"));

    }
}
