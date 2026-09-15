package com.tqx.leetcode;

import java.util.HashMap;

/**
 * @author Administrator
 * @version 1.0
 * @description:
 * 输入：nums = [2,7,11,15], target = 9
 * 输出：[0,1]
 * 解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
 * @date 2026/3/26 17:10
 */
public class Leetcode01 {

    public int[] twoSum(int[] nums, int target) {
        int[] res = new int[2];
        HashMap<Integer, Integer> map = new HashMap<>(nums.length);
        for (int i = 0; i < nums.length; i++) {
            int want = target - nums[i];
            if (map.containsKey(want)) {
                res[0] = i;
                res[1] = map.get(want);
                break;
            } else {
                map.put(nums[i], i);
            }
        }
        return res;
    }
}
