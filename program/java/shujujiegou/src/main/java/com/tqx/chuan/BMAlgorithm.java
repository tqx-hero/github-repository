package com.tqx.chuan;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 从子串后往前匹配，
 * 先看尾巴对不对，不对直接往后退
 * 尾巴对上倒着比，从头对完就胜利
 * 比坏字符算跳跃，最少一步不回头
 * @date 2026/4/12 14:11
 */
public class BMAlgorithm {

    public static int getIndex(String str, String s) {
        if (str == null || s == null || str.isEmpty() || s.isEmpty() || s.length() > str.length())
            return -1;
        char[] sArr = s.toCharArray();
        char[] strArr = str.toCharArray();
        var n = sArr.length;
        int m = strArr.length;

        //记录每个字符在模式串中出现的最末index
        //坏字符的最后下标存储结果
        int[] badChars = new int[256];
        Arrays.fill(badChars, -1);

        //好后缀处理解
        //好后缀即表示以当前下标为界后面的子串在前面子串出现的最长子串，用于在匹配过程中
        //发生匹配失败时让匹配成功部分直接前挪到正文串相关位置，不需要再次回溯
        //1、好后缀的最大长度
        int[] suffix = new int[n];
        //2、好后缀的起始下标
        int[] prefixIndex = new int[n];
        Arrays.fill(prefixIndex, -1);
        for (int i = 0; i < n; i++) {
            //坏字符的处理
            //以字符的ASCII值为下标将字符在模式串中最后出现的位置放到badChars数组中
            badChars[sArr[i]] = i;

            //好后缀的处理
            //以当前下标为界划分两个子串序列
            //跳过首尾无意义的两个下标
            if (i == 0 || i == n - 1)
                continue;
            //定义好后缀检测的指针
            int h = i - 1, t = n - 1;
            //记录好后缀的长度与起始下标
            int size = 0, cur = -1;
            //不相同则继续从后往前找
            //查看记录的长度是否超过suffix中记录的长度
            //超过则覆盖记录,并清空长度与下标的临时变量
            //清空临时记录，重新开始计数
            //相同则开始记录下标与长度，指针前移继续匹配
            //循环结束，再次查看记录，超过长度的再次记录
            for (; h >= 0 && t > i; h--) {
                if (sArr[h] != sArr[t]) {
                    if (size > 0)
                        break;
                    continue;
                }
                cur = h;
                t--;
                size++;
            }
            if (size > suffix[i]) {
                suffix[i] = size;
                prefixIndex[i] = cur;
            }
        }
        for (int i = n - 1; i < m; ) {
            if (sArr[n - 1] != strArr[i]) {
                i++;
                continue;
            }
            //正文串起始指针
            int p = i;
            //子串起始指针，末尾开始往前匹配
            int j = n - 1;
            for (; j >= 0 && strArr[p] == sArr[j]; p--, j--) ;
            //如果都匹配相同,直接返回下标位置
            if (j < 0)
                return ++p;
            //如果匹配失败，记录当前正文串中下标的字符
            //找到该字符在模式串中最后出现的的下标
            //如果找到，将模式串中该字符与正文串中的这个对齐
            //再重新在模式串中倒着比较
            int b = badChars[strArr[p]];
            int jump = b < 0 ? n : j - b;
            //如果出现跳跃步数为0或者负数的情况
            //比如b的位置，即最后出现的下标超过当前指示的下标
            //此时jump为负数，这样会往回退
            //为了避免这种情况，需要强制让它跳一步
            if (jump < 1)
                jump = 1;

            //好后缀的情况，要移动的步数
            if (prefixIndex[j] != -1) {
                //计算好后缀情况下要移动的步数
                int jmp = j - prefixIndex[j];
                //取两者最大值
                jump = Math.max(jmp, jump);
            }
            i += jump;
        }
        return -1;
    }

    public static void main(String[] args) {
        String str = "TTTTCACTCAC";
        String s = "CACTCAC";
        System.out.println(getIndex(str, s));
    }

}
