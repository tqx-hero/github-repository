package com.tqx.leetcode;

/**
 * @author Administrator
 * @version 1.0
 * @description: ￼
 * 代码
 * ￼
 * ￼
 * ￼
 * 测试用例
 * 测试用例
 * ￼
 * 测试结果
 * 11. 盛最多水的容器
 * ￼
 * 中等
 * ￼
 * 相关标签
 * ￼
 * 相关企业
 * ￼
 * 提示
 * ￼
 * 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
 * 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 * 返回容器可以储存的最大水量。
 * 说明：你不能倾斜容器。 
 * 示例 1：
 * 输入：
 * [1,8,6,2,5,4,8,3,7]
 * 输出：
 * 49
 * 解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
 * 示例 2：
 * 输入：
 * height = [1,1]
 * 输出：
 * 1
 *  提示：
 * • n == height.length
 * • 2 <= n <= 105
 * • 0 <= height[i] <= 104
 * @date 2026/5/13 21:57
 */
public class Leetcode11 {
    //容器盛水的多少取决于最短的那块木板的长度
    //两指针分别从数组的最左最右开始
    //计算面积，移动两者较小的那个指针，因为短的那个决定了面积的宽度，如果移动较大值的，宽度不变，长度
    //减1，面积肯定会减少，所以只能移动较小值的那个指针
    //一直到两指针重叠为止，取出面积最大值
    public static int maxArea(int[] height) {
        int length = height.length;
        int area = 0;
        for (int left = 0, right = length - 1; left < right; ) {
            int i = height[left];
            int j = height[right];
            int curArea = (right - left) * Math.min(i, j);
            area = Math.max(curArea, area);
            if (i > j)
                right--;
            else if (i < j)
                left++;
            else {
                left++;
                right--;
            }
        }
        return area;
    }

    public static void main(String[] args) {
        int[] arr = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        System.out.println(maxArea(arr));
    }
}
