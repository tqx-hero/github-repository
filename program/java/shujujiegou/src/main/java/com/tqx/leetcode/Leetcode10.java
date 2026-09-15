package com.tqx.leetcode;

import java.util.ArrayDeque;

/**
 * @author Administrator
 * @version 1.0
 * @description: 正则表达式
 * 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
 * <p>
 * '.' 匹配任意单个字符
 * '*' 匹配零个或多个前面的那一个元素
 * 返回一个布尔值，表示匹配是否覆盖整个输入字符串（而非部分）。
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * 输入：s = "aa", p = "a"
 * 输出：false
 * 解释："a" 无法匹配 "aa" 整个字符串。
 * 示例 2:
 * <p>
 * 输入：s = "aa", p = "a*"
 * 输出：true
 * 解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
 * 示例 3：
 * <p>
 * 输入：s = "ab", p = ".*"
 * 输出：true
 * 解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
 * <p>
 * <p>
 * 提示：
 * <p>
 * 1 <= s.length <= 20
 * 1 <= p.length <= 20
 * s 只包含从 a-z 的小写字母。
 * p 只包含从 a-z 的小写字母，以及字符 . 和 *。
 * 保证每次出现字符 * 时，前面都匹配到有效的字符
 * @date 2026/4/6 21:09
 */
public class Leetcode10 {

    public boolean isMatch(String s, String p) {
        ArrayDeque<Character> queue = new ArrayDeque<>();
        for (int i = 0; i < s.length(); i++) {
            queue.add(s.charAt(i));
        }
        int idx = 0;
        while (idx < p.length()) {
            char c = p.charAt(idx);
            if (c == '.') {
                queue.poll();
                idx++;
                continue;
            } else if (c == '*') {
                //前面是.则匹配所有字符
                if (p.charAt(idx - 1) == '.')
                    return true;
                //前面不是.
                //todo 没有思路,需要好好考虑考虑
            } else {
                Character qc = queue.peek();
                if (c != qc)
                    return false;
                queue.poll();
                idx++;
            }

        }

        return false;
    }

    static class Node {
        char c;
        Node next;
        Node prev;
    }


}
