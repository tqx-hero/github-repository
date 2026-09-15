package com.tqx.leetcode.slide_window;

import java.util.TreeSet;

/**
 * @author Administrator
 * @version 1.0
 * @description: 220. 存在重复元素 III
 * ￼
 * 困难
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 提示
 * ￼
 * 给你一个整数数组 nums 和两个整数 indexDiff 和 valueDiff 。
 * 找出满足下述条件的下标对 (i, j)：
 * • i != j,
 * • abs(i - j) <= indexDiff
 * • abs(nums[i] - nums[j]) <= valueDiff
 * 如果存在，返回 true ；否则，返回 false 。 
 * 示例 1：
 * 输入：
 * nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
 * 输出：
 * true
 * 解释：
 * 可以找出 (i, j) = (0, 3) 。
 * 满足下述 3 个条件：
 * i != j --> 0 != 3
 * abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
 * abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0
 * 示例 2：
 * 输入：
 * nums = [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3
 * 输出：
 * false
 * 解释：
 * 尝试所有可能的下标对 (i, j) ，均无法满足这 3 个条件，因此返回 false 。
 *  提示：
 * • 2 <= nums.length <= 105
 * • -109 <= nums[i] <= 109
 * • 1 <= indexDiff <= nums.length
 * • 0 <= valueDiff <= 109
 * @date 2026/5/23 23:03
 */
public class Leet220 {

    //滑动窗口
    // 将数据放到TreeSet中
    //当 j-i =k时，左右指针同时移动
    //并且每次都需要先计算nums[right]的所求值范围，即：[nums[right]-valueDiff,nums[right]+valueDiff]
    //在红黑树中查询有没有符合该条件的元素，有的话返回，没有则将nums[right]入set
    public static boolean containsNearbyAlmostDuplicate(int[] nums, int indexDiff, int valueDiff) {
        TreeSet<Integer> set = new TreeSet<>();
        for (int left = 0, right = 0; right < nums.length; right++) {
            int num = nums[right];
            //计算所查询值的区间
            int min = num - valueDiff;
            int max = num + valueDiff;
            //判断红黑树中有没有该区间的值
            //不空表示有，直接返回
            if (!set.subSet(min, true, max, true).isEmpty())
                return true;

            //空表示没有，将num入树
            set.add(num);
            if (right - left == indexDiff)
                set.remove(nums[left++]);
        }
        return false;
    }

    public static void main(String[] args) {
//        TreeSet<Integer> set = new TreeSet<>();
//        set.add(10);
//        set.add(5);
//        set.add(20);
//        set.add(15);
//        set.add(3);
//
//        // 1. 范围 [5, 15) → 包含5，不包含15
//        System.out.println(set.subSet(100, 150).isEmpty());  // [5,10]
//
//        // 2. 小于 15 的所有元素（≤15）
//        System.out.println(set.headSet(15));       // [3,5,10]
//
//        // 3. 大于等于 10 的所有元素
//        System.out.println(set.tailSet(10));       // [10,15,20]

        int [] nums ={1,5,9,1,5,9};
        int indexDiff = 2, valueDiff = 3;
        System.out.println(containsNearbyAlmostDuplicate(nums, indexDiff, valueDiff));
    }
}
