package com.tqx.leetcode;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 88. 合并两个有序数组
 * 简单
 * 相关标签
 * premium lock icon
 * 相关企业
 * 提示
 * 给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
 * <p>
 * 请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。
 * <p>
 * 注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。
 * <p>
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * 输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
 * 输出：[1,2,2,3,5,6]
 * 解释：需要合并 [1,2,3] 和 [2,5,6] 。
 * 合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
 * 示例 2：
 * <p>
 * 输入：nums1 = [1], m = 1, nums2 = [], n = 0
 * 输出：[1]
 * 解释：需要合并 [1] 和 [] 。
 * 合并结果是 [1] 。
 * 示例 3：
 * <p>
 * 输入：nums1 = [0], m = 0, nums2 = [1], n = 1
 * 输出：[1]
 * 解释：需要合并的数组是 [] 和 [1] 。
 * 合并结果是 [1] 。
 * 注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。
 * <p>
 * <p>
 * 提示：
 * <p>
 * nums1.length == m + n
 * nums2.length == n
 * 0 <= m, n <= 200
 * 1 <= m + n <= 200
 * -109 <= nums1[i], nums2[j] <= 109
 * <p>
 * <p>
 * 进阶：你可以设计实现一个时间复杂度为 O(m + n) 的算法解决此问题吗？
 * @date 2026/5/10 23:47
 */
public class Leetcode88 {
    //倒序插入
    //由于是非递减数组，直接从后往前比较大小
    //大的往后排，直到nums2所有数据都放到nums1即可
    //要注意当两者数据相同时，需要优先把nums2的数据放到后面
    //保证nums1的数据在前
    public static void merge(int[] nums1, int m, int[] nums2, int n) {
        if (m == 1 && n == 0)
            return;
        else if (m == 0 && n == 1) {
            nums1[0] = nums2[0];
            return;
        }
        int i = n - 1;
        for (int j = m - 1, cur = m + n - 1; i >= 0 && j >= 0; cur--) {
            //如果nums2的数据不小于nums1，放到nums1的cur位置
            if (nums2[i] >= nums1[j]) {
                nums1[cur] = nums2[i--];
            }
            //否则把nums1的数据放到cur
            else
                nums1[cur] = nums1[j--];
        }
        //如果i>=0说明nums2的数据没放完，nums1的数据已经排在后面，
        //直接从前往后复制nums2的数据到nums1数组即可
        if (i >= 0) System.arraycopy(nums2, 0, nums1, 0, i + 1);
    }

    public static void main(String[] args) {
//        int[] nums1 = {1, 2, 3, 0, 0, 0}, nums2 = {2, 5, 6};
        int[] nums1 = {2, 0}, nums2 = {1};
        int m = 1, n = 1;
        merge(nums1, m, nums2, n);
        System.out.println(Arrays.toString(nums1));
    }
}
