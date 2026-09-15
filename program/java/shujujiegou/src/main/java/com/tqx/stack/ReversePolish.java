package com.tqx.stack;

import java.util.ArrayDeque;

/**
 * @author Administrator
 * @version 1.0
 * @description: 逆波兰表达式
 * 思想是让运算符以及括号入栈，数字直接输出，当将运算符入栈时先查看栈顶运算符优先级
 * 如果优先级不低于当前运算符，代表需要先执行，所以将栈顶弹出，直到栈顶运算符优先级不低于当前运算符
 * 然后当前运算符入栈，遇到栈顶是(时，需要等待)匹配，才得将栈顶弹出，直接弹出直到(出来，然后继续之前的操作
 * 括号可以不输出
 * @date 2026/4/8 8:18
 */
public class ReversePolish {

    //判断字符c1是否比c2优先级高
    //c1代表往栈内压入的字符
    //c2表示栈顶字符
    //false需要先出栈在入栈
    private static boolean priority(char c1, char c2) {
        if (c1 == '(')
            return true;
        if (c1 == '-' || c1 == '+') {
            return c2 == '(';
        } else if (c1 == '*' || c1 == '/')
            return c2 == '-' || c2 == '+' || c2 == '(';
        return false;
    }

    public static void main(String[] args) {
//        System.out.println(ReversePolish.priority('/', '+'));
//        String str = "a+b*c+(d*e+f)*g";
//        String str = "1+2*3+(4*5+6)*7";
//        System.out.println(reverPl(str));
        System.out.println(ReversePolish.calculate("123*+45*6+7*+"));
        System.out.println(1 + 2 * 3 + (4 * 5 + 6) * 7);
    }

    private static boolean isCalculation(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
    }

    //中缀表达式转后缀表达式
    public static String reverPl(String str) {
        if (str == null || str.isEmpty())
            return str;
        ArrayDeque<Character> stack = new ArrayDeque<>();
        StringBuilder sb = new StringBuilder();
        for (char c : str.toCharArray()) {
            //非符号直接输出不入站
            if (!isCalculation(c)) {
                sb.append(c);
                continue;
            }
            //右括号直接弹栈，直到弹出(
            if (c == ')') {
                //需要弹出栈顶直到弹出(
                while (!stack.isEmpty()) {
                    char pop = stack.pop();
                    if (pop == '(')
                        break;
                    sb.append(pop);
                }
                //其他情况，判断是+-*/还是(
                //1、+- ，直接弹栈直到栈顶是(
                //2、*/，栈顶是*/直接弹，+-(不弹
                //3、(，直接入栈，优先级最高,不见)不弹栈
            } else {
                //如果优先级不大于栈顶字符，直接弹栈直到优先级大于栈顶
                while (!stack.isEmpty() && !priority(c, stack.peek())) {
                    sb.append(stack.pop());
                }
                stack.push(c);
            }
        }
        while (!stack.isEmpty())
            sb.append(stack.pop());
        return sb.toString();
    }

    public static int calculate(String str) {
        ArrayDeque<Integer> stack = new ArrayDeque<>();
        for (char c : str.toCharArray()) {
            //只要是数字就入栈
            if (Character.isDigit(c)) {
                stack.push(c - '0');
            } else {
                int res = 0;
                Integer i2 = stack.pop();
                Integer i1 = stack.pop();
                switch (c) {
                    case '-' -> res = i1 - i2;
                    case '+' -> res = i1 + i2;
                    case '*' -> res = i1 * i2;
                    case '/' -> res = i1 / i2;
                }
                stack.push(res);
            }
        }
        return stack.pop();
    }

}
