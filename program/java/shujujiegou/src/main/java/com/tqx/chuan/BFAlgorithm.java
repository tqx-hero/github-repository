package com.tqx.chuan;

/**
 * @author Administrator
 * @version 1.0
 * @description: 暴力破解子串在正文串中出现的位置
 * 正文串：aaaabcd
 * 子串：abc
 * @date 2026/4/12 12:02
 */
public class BFAlgorithm {

    public static int getIndex(String str, String s) {

        if (str == null || str.isEmpty() || s.isEmpty() || s.length() > str.length())
            return -1;
        var length = s.length();
        int strLen = str.length();
        int res = -1;
        for (var i = 0; i < strLen; i++) {
            //判断剩余正文串长度是否小于子串
            //小于直接返回不匹配
            if (strLen - i < length)
                return -1;
            var index = i;
            //如果首字母匹配,继续匹配，直到某个字符不匹配，退出循环，继续往前遍历
            for (var j = 0; j < length && s.charAt(j) == str.charAt(index); j++, index++) ;
            if (index - i == length)
                return i;
        }
        return res;
    }

    public static void main(String[] args) {
        String str = "aaaabcd";
        String s = "cda";
        System.out.println(getIndex(str, s));
    }
}
