package com.tqx.leetcode.slide_window;

import java.util.HashSet;
import java.util.Set;

/**
 * @author Administrator
 * @version 1.0
 * @description: 219. 存在重复元素 II
 * ￼
 * 简单
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 给你一个整数数组 nums 和一个整数 k ，判断数组中是否存在两个 不同的索引 i 和 j ，满足 nums[i] == nums[j] 且 abs(i - j) <= k 。如果存在，返回 true ；否则，返回 false 。 
 * 示例 1：
 * 输入：nums = [1,2,3,1], k
 * = 3
 * 输出：true
 * 示例 2：
 * 输入：nums = [1,0,1,1], k =
 * 1
 * 输出：true
 * 示例 3：
 * 输入：nums = [1,2,3,1,2,3], k =
 * 2
 * 输出：false  
 * 提示：
 * • 1 <= nums.length <= 105
 * • -109 <= nums[i] <= 109
 * • 0 <= k <= 105
 * @date 2026/5/23 22:29
 */
public class Leet219 {
    //滑动窗口，k为窗口大小
    //设置左右指针left、right
    //使right - left <=k,
    //同时将数组元素放入set(哈希表)集合,
    //当窗口大小=k时，分别左右指针前移，
    //去掉左指针移出去的那个元素，判断右指针指向的元素是否存在
    //不存在则添加到Set，直到right=len-1
    public static boolean containsNearbyDuplicate(int[] nums, int k) {
        if (k == 0)
            return false;
        int length = nums.length;
        if (length == 1)
            return false;
        Set<Integer> set = new HashSet<>();
        for (int left = 0, right = 0; right < length; right++) {
            int num = nums[right];
            //集合中包含右指针的元素吗
            //包含，直接返回
            if (set.contains(num))
                return true;

            //不包含，将元素添加到set
            set.add(num);
            //等于k的时候，判断，同时需要移动左指针，把左指针的元素移出set
            if (right - left == k)
                set.remove(nums[left++]);
        }
        return false;
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3, 1};
        System.out.println(containsNearbyDuplicate(nums, 3));
    }

}
