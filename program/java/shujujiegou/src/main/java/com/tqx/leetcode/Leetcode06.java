package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 代码
 * <p>
 * <p>
 * 测试用例
 * 测试用例
 * 测试结果
 * 6. Z 字形变换
 * 中等
 * 相关标签
 * premium lock icon
 * 相关企业
 * 将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。
 * <p>
 * 比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：
 * <p>
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。
 * <p>
 * 请你实现这个将字符串进行指定行数变换的函数：
 * <p>
 * string convert(string s, int numRows);
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * 输入：s = "PAYPALISHIRING", numRows = 3
 * 输出："PAHNAPLSIIGYIR"
 * 示例 2：
 * 输入：s = "PAYPALISHIRING", numRows = 4
 * 输出："PINALSIGYAHRPI"
 * 解释：
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 * 示例 3：
 * <p>
 * 输入：s = "A", numRows = 1
 * 输出："A"
 * <p>
 * <p>
 * 提示：
 * <p>
 * 1 <= s.length <= 1000
 * s 由英文字母（小写和大写）、',' 和 '.' 组成
 * 1 <= numRows <= 1000
 * @date 2026/3/31 18:48
 */
public class Leetcode06 {

    public static void main(String[] args) {
//        System.out.println("PAYPALISHIRING".length());
//        String str = "PAYPALISHIRING";
//        String str = "A";
        String str = "Apalindromeisaword,phrase,number,orothersequenceofunitsthatcanbereadthesamewayineitherdirection,withgeneralallowancesforadjustmentstopunctuationandworddividers.";
        System.out.println(str.length());
        System.out.println(getColumn(str.length(), 10));
//        System.out.println(14 % 8);
        System.out.println(convert(str, 10));
    }


    public static String convert(String s, int numRows) {
        if (s == null || s.isEmpty() || numRows < 1)
            return "";
        if (numRows == 1)
            return s;
        int len = s.length();
        int r = numRows - 1;
        //计算列数,字符串长度<2倍总长度，直接取模，否则：
        // 列数 = len/(2(n-1)) + len%(2(n-1))/(n-1)向上取整
        //其中len为字符串长度，n为输入的行数
        int column = getColumn(len, numRows);
        char[][] strArr = new char[numRows][column];
        int index = 0;
        for (int i = 0; i < column && index < len; i++) {
            int rem = i % r;
            //整除的存放numRows个
            if (rem == 0) {
                for (int j = 0; j < numRows && index < len; j++) {
                    strArr[j][i] = s.charAt(index++);
                }
                continue;
            }
            //不整除的放1个，位置为((n-1)-i%(n-1),i)
            //n为行数，i为列的下标
            int colIndex = r - rem;
            strArr[colIndex][i] = s.charAt(index++);
        }

        //拼接字符串
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < column; j++) {
                char c = strArr[i][j];
                if (c != 0) {
                    builder.append(c);
                }
            }
        }
        return builder.toString();
    }

    public static int getColumn(int len, int row) {
        int r = row - 1;
        int i = r << 1;
        int num = len / i;
        int remainder = len % i;
        int col = num * r;
        if (remainder > 0) {
            col += Math.min(remainder, row);
        }
        return col;
    }
}
