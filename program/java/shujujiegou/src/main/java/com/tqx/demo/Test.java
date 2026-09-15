package com.tqx.demo;

import java.util.ArrayDeque;

/**
 * @author Administrator
 * @version 1.0
 * @description: 字符串括号匹配
 * @date 2026/3/27 13:55
 */
public class Test {

    public static boolean ts(String s) {
        if (s == null || s.isEmpty())
            return false;
        ArrayDeque<Character> stack = new ArrayDeque<>();
        for (char c : s.toCharArray()) {
            if (c == '{' || c == '[' || c == '(')
                stack.push(c);
            else {
                if (stack.isEmpty())
                    return false;
                char p = stack.pop();
                if ((c == '}' && p != '{')
                        || (c == ']' && p != '[')
                        || (c == ')' && p != '(')
                )
                    return false;
            }
        }
        return stack.isEmpty();
    }

    public static void main(String[] args) {
        String str = "([][]{}())";
//        String str = "{[}]";
        System.out.println(Test.ts(str));
    }
}
