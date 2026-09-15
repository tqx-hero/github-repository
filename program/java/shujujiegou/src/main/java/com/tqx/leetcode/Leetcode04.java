package com.tqx.leetcode;

import java.util.Collections;
import java.util.PriorityQueue;

/**
 * @author Administrator
 * @version 1.0
 * @description: 求两数组的中位数
 * 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
 * 算法的时间复杂度应该为 O(log (m+n)) 。 
 * 示例 1：
 * 输入：
 * nums1 = [1,3], nums2 = [2]
 * 输出：
 * 2.00000
 * 解释：
 * 合并数组 = [1,2,3] ，中位数 2
 * 示例 2：
 * 输入：
 * nums1 = [1,2], nums2 = [3,4]
 * 输出：
 * 2.50000
 * 解释：
 * 合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 * @date 2026/3/27 7:09
 */
public class Leetcode04 {

    public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
        if (nums1.length == 0 && nums2.length == 0) {
            return 0.00;
        }
        //定义大小顶堆，大顶堆存放较小的一半数，小顶堆放大数，
        // 保持两堆的数据量差最多1
        PriorityQueue<Integer> littleTopHeap = new PriorityQueue<>();
        PriorityQueue<Integer> bigTopHeap = new PriorityQueue<>(Collections.reverseOrder());
        for (int i = 0; i < nums1.length; i++) {
            if (!littleTopHeap.isEmpty() && nums1[i] >= littleTopHeap.peek())
                littleTopHeap.add(nums1[i]);
            else
                bigTopHeap.add(nums1[i]);

            if (bigTopHeap.size() - littleTopHeap.size() > 1) {
                littleTopHeap.add(bigTopHeap.poll());
            } else if (littleTopHeap.size() - bigTopHeap.size() >= 1) {
                bigTopHeap.add(littleTopHeap.poll());
            }
        }
        for (int i = 0; i < nums2.length; i++) {
            if (!littleTopHeap.isEmpty() && nums2[i] >= littleTopHeap.peek())
                littleTopHeap.add(nums2[i]);
            else
                bigTopHeap.add(nums2[i]);

            if (bigTopHeap.size() - littleTopHeap.size() > 1) {
                littleTopHeap.add(bigTopHeap.poll());
            } else if (littleTopHeap.size() - bigTopHeap.size() >= 1) {
                bigTopHeap.add(littleTopHeap.poll());
            }
        }
        //奇数取大顶堆堆顶，偶数取两个堆顶平均数
        double num;
        if ((nums1.length + nums2.length) % 2 == 0)
            num = (double) (bigTopHeap.peek() + littleTopHeap.peek()) / 2;
        else
            num = (double) bigTopHeap.peek();
        return num;
    }

    public static void main(String[] args) {
        System.out.println(findMedianSortedArrays(new int[]{1, 2}, new int[]{3, 4}));
    }
}
