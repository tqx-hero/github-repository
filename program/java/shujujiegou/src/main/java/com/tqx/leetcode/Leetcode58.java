package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: ￼
 * 代码
 * ￼
 * 测试用例
 * 测试用例
 * ￼
 * 测试结果
 * 58. 最后一个单词的长度
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给你一个字符串 s，由若干单词组成，单词前后用一些空格字符隔开。返回字符串中 最后一个 单词的长度。
 * 单词 是指仅由字母组成、不包含任何空格字符的最大子字符串。 
 * 示例 1：
 * 输入：
 * s = "Hello World"
 * 输出：
 * 5
 * 解释：
 * 最后一个单词是“World”，长度为 5。
 * 示例 2：
 * 输入：
 * s = "   fly me   to   the moon  "
 * 输出：4
 * 解释：
 * 最后一个单词是“moon”，长度为 4。
 * 示例 3：
 * 输入：
 * s = "luffy is still joyboy"
 * 输出：
 * 6
 * 解释：
 * 最后一个单词是长度为 6 的“joyboy”。
 *  提示：
 * • 1 <= s.length <= 104
 * • s 仅有英文字母和空格 ' ' 组成
 * • s 中至少存在一个单词
 * @date 2026/5/11 17:23
 */
public class Leetcode58 {
    //倒序比较，从后往前直接开始比，忽略空格，从出现第一个字母开始计数
    //直到再次出现空格停止计数，两个索引相减即可
    public static int lengthOfLastWord(String s) {
        int length = s.length();
        if (length == 1)
            return 1;
        char space = ' ';
        int end = length - 1;
        //去除字符串最后面的所有空格,得到有效字符的起始位置
        while (s.charAt(end) == space)
            end--;
        int begin = end;
        while (begin >= 0 && s.charAt(begin) != space)
            begin--;
        return end - begin;
    }

    public static void main(String[] args) {
        String s = "joyboy           ";
        System.out.println(lengthOfLastWord(s));
    }
}
