package com.tqx.leetcode;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 349. 两个数组的交集
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给定两个数组 nums1 和 nums2 ，返回 它们的 交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。 
 * 示例 1：
 * 输入：
 * nums1 = [1,2,2,1], nums2 = [2,2]
 * 输出：
 * [2]
 * 示例 2：
 * 输入：
 * nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * 输出：
 * [9,4]
 * 解释：
 * [4,9] 也是可通过的
 *  提示：
 * • 1 <= nums1.length, nums2.length <= 1000
 * • 0 <= nums1[i], nums2[i] <= 1000
 * @date 2026/5/12 0:01
 */
public class Leetcode349 {

    public static int[] intersection(int[] nums1, int[] nums2) {
        Set<Integer> set = new HashSet<>();
        Set<Integer> list = new HashSet<>();
        for (int i = 0; i < nums1.length; i++)
            set.add(nums1[i]);
        for (int j = 0; j < nums2.length; j++) {
            int n2 = nums2[j];
            if (set.contains(n2))
                list.add(n2);
        }
        int[] result = new int[list.size()];
        int idx = 0;
        for (Integer i : list)
            result[idx++] = i;
        return result;
    }

    public static void main(String[] args) {
        int[] nums1 = {4, 9, 5}, nums2 = {9, 4, 9, 8, 4};
        System.out.println(Arrays.toString(intersection(nums1, nums2)));
    }

}
