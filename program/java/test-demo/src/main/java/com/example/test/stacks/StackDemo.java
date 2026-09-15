package com.example.test.stacks;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 使用ArrayDeque实现栈对数据的运算
 * @date 2026/2/25 20:39
 */
public class StackDemo {

    //定义存放数值的栈
    public static ArrayDeque<Integer> intStack = new ArrayDeque<>();
    //定义存放运算符和括号的栈
    public static ArrayDeque<Character> charStack = new ArrayDeque<>();

    //获取运算优先级
    public static Integer getPriority(char ch) {
        if (ch == '*' || ch == '/')
            return 2;
        else if (ch == '+' || ch == '-')
            return 1;
        return 0;
    }


    public static void doMath() {
        Integer popLater = intStack.pop();
        Integer popFirst = intStack.pop();
        Character opt = charStack.pop();
        int i = 0;
        if (opt == '+') {
            i = popFirst + popLater;
        } else if (opt == '-') {
            i = popFirst - popLater;
        } else if (opt == '*') {
            i = popFirst * popLater;
        } else if (opt == '/') {
            i = popFirst / popLater;
        }
        intStack.push(i);
    }


    public static Integer getMath(String num) {

//        char[] charArray = forMatStr(num);
        char[] charArray = num.toCharArray();
        int result = 0;
        try {
            for (int i = 0; i < charArray.length; i++) {
                //去掉空格
                if (Character.isWhitespace(charArray[i]))
                    continue;
                //数值放入数值栈
                if (Character.isDigit(charArray[i])) {
                    intStack.push(Character.getNumericValue(charArray[i]));
                }
                //运算符放入运算符栈
                else {
                    if (charStack.isEmpty() || charArray[i] == '(') {
                        charStack.push(charArray[i]);
                        continue;
                    }
                    if (charArray[i] != ')' && getPriority(charStack.peek()) >= getPriority(charArray[i])) {
                        do {
                            doMath();
                            if (charStack.isEmpty()) {
                                break;
                            }
                        } while (charStack.peek() != '(' && getPriority(charStack.peek()) >= getPriority(charArray[i]));
                        charStack.push(charArray[i]);
                        continue;
                    }
                    if (charArray[i] == ')') {
                        if (charStack.peek() != '(') {
                            do {
                                doMath();
                                if (charStack.isEmpty()) {
                                    break;
                                }
                            } while (charStack.peek() != '(');
                        }
                        charStack.pop();
                        continue;
                    }
                    charStack.push(charArray[i]);

                }
            }
            if (!charStack.isEmpty()) {
                while (!charStack.isEmpty()) {
                    doMath();
                }
            }
            result = intStack.pop();
        } finally {
            if (!intStack.isEmpty())
                intStack.remove();
            if (!charStack.isEmpty())
                charStack.remove();
        }


        return result;
    }

    public static boolean isPatton(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
    }

    public static char[] forMatStr(String str) {
        char[] chars = str.toCharArray();

        char[] charArray = new char[chars.length];
        String strs = "";
        List<Character> charList = new ArrayList<>();
        for (int i = 0; i < chars.length; i++) {
            if (Character.isDigit(chars[i])) {
                strs += chars[i];
            } else {
                if (!strs.equals("")) {
                    charList.add((char) (' ' + Integer.parseInt(strs)));
                }
                charList.add(chars[i]);
                strs = "";
            }
        }

        for (int i = 0; i < charList.size(); i++) {
            charArray[i] = charList.get(i);
        }
        return charArray;
    }

    public static void main(String[] args) {
        String i = "9 + 3 * ((2 +3+ 2+3*7+2)+2) + 6 / 2";
//        String j1 = "9 + 10 * (2 + 3) + 6 / 2+11*5+3+2+1";

        System.out.println("格式化str==" + forMatStr(i));
        i = i.replaceAll("\\s+", "");
        System.out.println("栈计算=" + getMath(i));

        System.out.println("实际计算=" + (9 + 3 * ((2 + 3 + 2 + 3 * 7 + 2) + 2) + 6 / 2));
    }

}
