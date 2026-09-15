package com.tqx.leetcode;

import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 14. 最长公共前缀
 * 简单
 * 相关标签
 * premium lock icon
 * 相关企业
 * 编写一个函数来查找字符串数组中的最长公共前缀。
 * <p>
 * 如果不存在公共前缀，返回空字符串 ""。
 * <p>
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * 输入：strs = ["flower","flow","flight"]
 * 输出："fl"
 * 示例 2：
 * <p>
 * 输入：strs = ["dog","racecar","car"]
 * 输出：""
 * 解释：输入不存在公共前缀。
 * <p>
 * <p>
 * 提示：
 * <p>
 * 1 <= strs.length <= 200
 * 0 <= strs[i].length <= 200
 * strs[i] 如果非空，则仅由小写英文字母组成
 * @date 2026/5/4 20:46
 */
public class Leetcode14 {
    public static String longestCommonPrefix(String[] strs) {
        //1、数组长度为1时，直接返回
        if (strs.length == 1)
            return strs[0];
        int len = strs.length;
        int i = 0;
        //将每个数组字符串长度放入
        int[] lens = new int[len];
        //对每个元素判空，有为空的直接返回""
        for (; i < len && !strs[i].isBlank(); i++)
            lens[i] = strs[i].length();
        if (i < len)
            return "";
        //重置下标i
        i = 0;
        //因为i必然小于每个字符串的长度，
        // 所以可以
        // 令i小与数组第一个字符串的长度
        //这样直接拿取第0位的字符串下标为i的那个字符作为比较对象
        while (i < lens[0]) {
            char c = strs[0].charAt(i);
            //遍历每个字符串数组元素的下标，一一比对char
            int k = 1;
            for (; k < len && lens[k] > i && strs[k].charAt(i) == c; k++) ;
            //判断k是否与len相同，小于则说明下标为i的字符比对失败
            //最长前缀匹配下标为0~i-1
            if (k < len) {
                i--;
                break;
            }
            //k与len相同，i下标匹配成功，+1继续循环
            else
                i++;
        }
        //截取字符串0~i
        return strs[0].substring(0, Math.min(++i, lens[0]));
    }

    public static void main(String[] args) {
//        System.out.println("   ".isBlank());
//        String[] strs = {"flower","flow","flight"};
//        String[] strs = {"dog","racecar","     "};
//        String[] strs = {"ab", "a"};
        String[] strs = {"flower", "flower", "flower", "flower"};
        System.out.println(longestCommonPrefix(strs));
    }
}
