package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 字符串转整数
 * 请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数。
 * <p>
 * 函数 myAtoi(string s) 的算法如下：
 * <p>
 * 空格：读入字符串并丢弃无用的前导空格（" "）
 * 符号：检查下一个字符（假设还未到字符末尾）为 '-' 还是 '+'。如果两者都不存在，则假定结果为正。
 * 转换：通过跳过前置零来读取该整数，直到遇到非数字字符或到达字符串的结尾。如果没有读取数字，则结果为0。
 * 舍入：如果整数数超过 32 位有符号整数范围 [−231,  231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被舍入为 −231 ，大于 231 − 1 的整数应该被舍入为 231 − 1 。
 * 返回整数作为最终结果。
 * <p>
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * 输入：s = "42"
 * <p>
 * 输出：42
 * <p>
 * 解释：加粗的字符串为已经读入的字符，插入符号是当前读取的字符。
 * <p>
 * 带下划线线的字符是所读的内容，插入符号是当前读入位置。
 * 第 1 步："42"（当前没有读入字符，因为没有前导空格）
 * ^
 * 第 2 步："42"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
 * ^
 * 第 3 步："42"（读入 "42"）
 * ^
 * 示例 2：
 * <p>
 * 输入：s = " -042"
 * <p>
 * 输出：-42
 * <p>
 * 解释：
 * <p>
 * 第 1 步："   -042"（读入前导空格，但忽视掉）
 * ^
 * 第 2 步："   -042"（读入 '-' 字符，所以结果应该是负数）
 * ^
 * 第 3 步："   -042"（读入 "042"，在结果中忽略前导零）
 * ^
 * 示例 3：
 * <p>
 * 输入：s = "1337c0d3"
 * <p>
 * 输出：1337
 * <p>
 * 解释：
 * <p>
 * 第 1 步："1337c0d3"（当前没有读入字符，因为没有前导空格）
 * ^
 * 第 2 步："1337c0d3"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
 * ^
 * 第 3 步："1337c0d3"（读入 "1337"；由于下一个字符不是一个数字，所以读入停止）
 * ^
 * 示例 4：
 * <p>
 * 输入：s = "0-1"
 * <p>
 * 输出：0
 * <p>
 * 解释：
 * <p>
 * 第 1 步："0-1" (当前没有读入字符，因为没有前导空格)
 * ^
 * 第 2 步："0-1" (当前没有读入字符，因为这里不存在 '-' 或者 '+')
 * ^
 * 第 3 步："0-1" (读入 "0"；由于下一个字符不是一个数字，所以读入停止)
 * ^
 * 示例 5：
 * <p>
 * 输入：s = "words and 987"
 * <p>
 * 输出：0
 * <p>
 * 解释：
 * <p>
 * 读取在第一个非数字字符“w”处停止。
 * <p>
 * <p>
 * <p>
 * 提示：
 * <p>
 * 0 <= s.length <= 200
 * s 由英文字母（大写和小写）、数字（0-9）、' '、'+'、'-' 和 '.' 组成
 * @date 2026/3/31 22:00
 */
public class Leetcode08 {

    public static int myAtoi(String s) {
        if (s == null || s.isEmpty())
            return 0;
        s = s.strip();
        StringBuilder sb = new StringBuilder();
        boolean flag = false;
        boolean allowZero = true;
        for (int index = 0; index < s.length(); index++) {
            char c = s.charAt(index);
            if (index == 0) {
                if (c == '-') {
                    flag = true;
                    continue;
                } else if (c == '+') {
                    continue;
                } else if (!Character.isDigit(c)) {
                    return 0;
                } else if (c != '0') {
                    allowZero = false;
                }
            }
            if (!Character.isDigit(c))
                break;
            else if (c != '0' && allowZero) {
                allowZero = false;
            } else if (c == '0' && allowZero)
                continue;
            sb.append(c);
            if (sb.length() > 12)
                break;
        }
        if (sb.isEmpty())
            return 0;
        String newStr = flag ? "-" + sb : sb.toString();
        Long l = Long.valueOf(newStr);
        if (l < Integer.MIN_VALUE)
            return Integer.MIN_VALUE;
        if (l > Integer.MAX_VALUE)
            return Integer.MAX_VALUE;
        return Integer.parseInt(newStr);
    }

    public static int myAtois(String s) {
        if (s == null || s.isEmpty())
            return 0;
        String str = s.strip();
        int i = 0;
        boolean isMi = false;
        int result = 0;
        while (i < str.length()) {
            char c = str.charAt(i);
            if (i == 0) {
                if (c == '-') {
                    isMi = true;
                    i++;
                    continue;
                } else if (c == '+') {
                    i++;
                    continue;
                }
            }
            if (!Character.isDigit(c))
                break;
            int now = c - '0';
            if (!isMi && (result > Integer.MAX_VALUE/10
                    || (result == Integer.MAX_VALUE/10 &&
                    now >7)))
                return Integer.MAX_VALUE;
            else if (isMi &&
                    (-result < Integer.MIN_VALUE/10
                    || (-result == Integer.MIN_VALUE/10
                    && now>8)))
                return Integer.MIN_VALUE;
            result = result * 10 + now;
            i++;
        }
        return isMi ? -result : result;
    }

    public static void main(String[] args) {
//        String s = " +042";
//        String s = "010";
        String s = "-2147483649";
//        char str = '0';
//        String s = "20000000000000000000";
        System.out.println(myAtois(s));
//        System.out.println(str == '0');
//        System.out.println(myAtoi(s));
//        System.out.println(Character.isDigit('-'));

//        System.out.println(-10 * 10);
    }
}
