package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: 35. 搜索插入位置
 * 简单
 * 相关标签
 * premium lock icon
 * 相关企业
 * 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
 * <p>
 * 请必须使用时间复杂度为 O(log n) 的算法。
 * <p>
 * <p>
 * <p>
 * 示例 1:
 * <p>
 * 输入: nums = [1,3,5,6], target = 5
 * 输出: 2
 * 示例 2:
 * <p>
 * 输入: nums = [1,3,5,6], target = 2
 * 输出: 1
 * 示例 3:
 * <p>
 * 输入: nums = [1,3,5,6], target = 7
 * 输出: 4
 * <p>
 * <p>
 * 提示:
 * <p>
 * 1 <= nums.length <= 104
 * -104 <= nums[i] <= 104
 * nums 为 无重复元素 的 升序 排列数组
 * -104 <= target <= 104
 * @date 2026/5/11 17:07
 */
public class Leetcode35 {
    //二分查找
    public static int searchInsert(int[] nums, int target) {
        int len = nums.length;
        if (len == 1)
            return target <= nums[0] ? 0 : 1;
        int left = 0;
        for (int right = len - 1; left <= right; ) {
            int mid = left + (right - left) / 2;
            int cmp = nums[mid];
            if (cmp == target)
                return mid;
            else if (cmp > target)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3, 5, 6};
        int target = 2;
        System.out.println(searchInsert(nums, target));
    }
}
