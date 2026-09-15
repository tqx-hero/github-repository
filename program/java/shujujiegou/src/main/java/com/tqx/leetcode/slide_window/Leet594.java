package com.tqx.leetcode.slide_window;

import java.util.HashMap;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @description: 594. 最长和谐子序列
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 和谐数组是指一个数组里元素的最大值和最小值之间的差别 正好是 1 。
 * 给你一个整数数组 nums ，请你在所有可能的 子序列 中找到最长的和谐子序列的长度。
 * 数组的 子序列 是一个由数组派生出来的序列，它可以通过删除一些元素或不删除元素、且不改变其余元素的顺序而得到。 
 * 示例 1：
 * 输入：nums = [1,3,2,2,5,2,3,7]
 * 输出：5
 * 解释：
 * 最长和谐子序列是 [3,2,2,2,3]。
 * 示例 2：
 * 输入：nums = [1,2,3,4]
 * 输出：2
 * 解释：
 * 最长和谐子序列是 [1,2]，[2,3] 和 [3,4]，长度都为 2。
 * 示例 3：
 * 输入：nums = [1,1,1,1]
 * 输出：0
 * 解释：
 * 不存在和谐子序列。 
 * 提示：
 * • 1 <= nums.length <= 2 * 104
 * • -109 <= nums[i] <= 109
 * @date 2026/5/24 19:12
 */
public class Leet594 {

    public static int findLHS(int[] nums) {
        Map<Integer, Integer> map = new HashMap<>();
        int len = nums.length;
        if (len == 1)
            return 0;
        int maxCount = 0;
        for (int num : nums) {
            int min = num - 1;
            int max = num + 1;
            //不包含数，则添加数
            //统计map中这个数的数量
            int curNum = 1, maCount = 0, minCount = 0;
            if (!map.containsKey(num)) {
                map.put(num, 1);
            } else {
                curNum += map.get(num);
                map.put(num, curNum);
            }
            boolean bigExits = map.containsKey(max);
            boolean smallExits = map.containsKey(min);
            //如果两者都不存在，不更新maxCount
            if (!bigExits && !smallExits)
                continue;
            //查看较大值与较小值是否存在
            if (bigExits)
                maCount = map.get(max);
            if (smallExits)
                minCount = map.get(min);
            maxCount = Math.max(maxCount, curNum + Math.max(maCount, minCount));
        }
        return maxCount;
    }

    public static void main(String[] args) {
//        int[] nums = {1, 3, 2, 2, 5, 2, 3, 7};
        int[] nums = {1, 1,1,2};
//        int[] nums = {1, 2, 3, 4};
        System.out.println(findLHS(nums));
    }
}
