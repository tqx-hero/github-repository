package com.tqx.leetcode;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 119. 杨辉三角 II
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给定一个非负索引 rowIndex，返回「杨辉三角」的第 rowIndex 行。
 * 在「杨辉三角」中，每个数是它左上方和右上方的数的和。 
 * 示例 1:
 * 输入:
 * rowIndex = 3
 * 输出:
 * [1,3,3,1]
 * 示例 2:
 * 输入:
 * rowIndex = 0
 * 输出:
 * [1]
 * 示例 3:
 * 输入:
 * rowIndex = 1
 * 输出:
 * [1,1]
 *  提示:
 * • 0 <= rowIndex <= 33 
 * 进阶：
 * 你可以优化你的算法到 O(rowIndex) 空间复杂度吗？
 * @date 2026/5/12 23:17
 */
public class Leetcode119 {

    public static List<Integer> getRow(int rowIndex) {
        List<Integer> list = new ArrayList<>(rowIndex + 1);
        list.add(1);
        if (rowIndex == 0)
            return list;
        for (int i = 1; i <= rowIndex; i++) {
            int tmp = 1;
            for (int j = 1; j < i; j++) {
                Integer i1 = list.get(j);
                list.set(j, i1 + tmp);
                tmp = i1;
            }
            list.add(i, 1);
        }
        return list;
    }

    public static void main(String[] args) {
        System.out.println(getRow(4));
    }
}
