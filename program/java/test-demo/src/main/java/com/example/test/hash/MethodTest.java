package com.example.test.hash;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/27 12:58
 */
public class MethodTest {

    // {2,5,7,9,11,11,11,11,11,11,11}  tar= 12

    static int[] res(int[] nums, int target) {

        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int tag = target - nums[i];
            if (map.containsKey(tag)) {
                int[] res = {i, map.get(tag)};
                return res;
            }
            map.put(nums[i], i);
        }
        return null;

    }

    public static void main(String[] args) {
        int[] arr = {2, 5, 9, 11, 11, 11, 11, 11, 11, 11, 8};
//        int[] arr = {2, 5, 7, 9};
        long startTime = System.currentTimeMillis();
        int[] res = res(arr, 17);
        long endTime = System.currentTimeMillis();
        long time = endTime - startTime;
        System.out.println(Arrays.toString(res) + "，执行时间：" + time);

    }

}
