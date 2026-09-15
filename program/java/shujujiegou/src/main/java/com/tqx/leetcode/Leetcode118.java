package com.tqx.leetcode;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 118. 杨辉三角
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。
 * 在「杨辉三角」中，每个数是它左上方和右上方的数的和。 
 * 示例 1:
 * 输入:
 * numRows = 5
 * 输出:
 * [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
 * 示例 2:
 * 输入:
 * numRows = 1
 * 输出:
 * [[1]]
 *  提示:
 * • 1 <= numRows <= 30
 * @date 2026/5/12 22:45
 */
public class Leetcode118 {

    public static List<List<Integer>> generate(int numRows) {
        List<List<Integer>> res = new ArrayList<>(numRows);
        res.add(List.of(1));
        if (numRows == 1)
            return res;
        //加载l2
        res.add(List.of(1, 1));
        //从第三行开始
        for (int k = 2; k < numRows; k++) {
            List<Integer> lk = res.get(k - 1);
            List<Integer> lkNew = new ArrayList<>(k + 1);
            lkNew.add(1);
            int i = k >> 1;
            for (int j = 1; j <= i; j++)
                lkNew.add(lk.get(j - 1) + lk.get(j));
            for (int m = i + 1; m <= k; m++)
                lkNew.add(lkNew.get(k - m));
            res.add(lkNew);
        }
        return res;
    }

    public static void main(String[] args) {
        System.out.println(generate(5));
    }
}
