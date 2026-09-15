package com.tqx.leetcode.slide_window;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 187. 重复的DNA序列
 * ￼
 * 中等
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * DNA序列 由一系列核苷酸组成，缩写为 'A', 'C', 'G' 和 'T'.。
 * • 例如，"ACGAATTCCG" 是一个 DNA序列 。
 * 在研究 DNA 时，识别 DNA 中的重复序列非常有用。
 * 给定一个表示 DNA序列 的字符串 s ，返回所有在 DNA 分子中出现不止一次的 长度为 10 的序列(子字符串)。你可以按 任意顺序 返回答案。 
 * 示例 1：
 * 输入：
 * s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
 * 输出：
 * ["AAAAACCCCC","CCCCCAAAAA"]
 * 示例 2：
 * 输入：
 * s = "AAAAAAAAAAAAA"
 * 输出：
 * ["AAAAAAAAAA"]
 *  提示：
 * • 0 <= s.length <= 105
 * • s[i]=='A'、'C'、'G' or 'T'
 * @date 2026/5/24 18:12
 */
public class Leet187 {

    public static List<String> findRepeatedDnaSequences(String s) {
        List<String> list = new ArrayList<>();
        int len = s.length();
        if (len <= 10)
            return list;
        Set<String> set = new HashSet<>();
        Set<String> cmpSet = new HashSet<>();
        cmpSet.add(s.substring(0,10));
        for (int left = 1, right = 11; right <= len; right++, left++) {
            String str = s.substring(left,right);
            //如果map不存在字符串
            if (!cmpSet.contains(str)) {
                cmpSet.add(str);
            } else {
                set.add(str);
            }
        }
        list.addAll(set);
        return list;
    }

    public static void main(String[] args) {
        String s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
        System.out.println(findRepeatedDnaSequences(s));
//        System.out.println(s.substring(0, s.length()-1));
    }
}
