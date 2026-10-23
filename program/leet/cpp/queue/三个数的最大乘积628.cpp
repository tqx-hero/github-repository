//
// Created by Administrator on 2026/7/26.
//
/**
 * 628. 三个数的最大乘积
简单
相关标签
premium lock icon
相关企业
给你一个整型数组 nums ，在数组中找出由三个数组成的最大乘积，并输出这个乘积。



示例 1：

输入：nums = [1,2,3]
输出：6
示例 2：

输入：nums = [1,2,3,4]
输出：24
示例 3：

输入：nums = [-1,-2,-3]
输出：-6


提示：

3 <= nums.length <= 104
-1000 <= nums[i] <= 1000
 * @return
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumProduct(vector<int> &nums) {
        if (nums.size() == 3)
            return nums[0] * nums[1] * nums[2];
        vector<int> negativeNumbers, naturalNumbers;
        for (int n: nums) {
            if (n >= 0)
                naturalNumbers.push_back(n);
            else
                negativeNumbers.push_back(n);
        }
        std::sort(negativeNumbers.begin(), negativeNumbers.end());
        std::sort(naturalNumbers.begin(), naturalNumbers.end());
        //全部都是负数,需要取最大的三个负数相乘
        int naturalSize = naturalNumbers.size(), negativeSize = negativeNumbers.size();
        if (!naturalSize)
            return negativeNumbers[negativeSize-1] * negativeNumbers[negativeSize-2] * negativeNumbers[negativeSize-3];
        //有正数情况,先获取最大值

        int maxNum = naturalNumbers[naturalSize - 1], currentResult = 0;
        //大于0的数超过2个，先计算最大三个自然数的乘积
        if (naturalSize > 2)
            currentResult = maxNum * naturalNumbers[naturalSize - 2] * naturalNumbers[naturalSize - 3];

        //如果负数超过1个，计算2个最小负数乘积，并与最大的正数相乘，比较上面的结果
        if (negativeSize > 1)
            currentResult = max(maxNum * negativeNumbers[0] * negativeNumbers[1], currentResult);
        return currentResult;
    }
};

// int main() {
//     // priority_queue<int, vector<int>, greater<> > test;
//     // test.push(10);
//     // test.push(11);
//     // test.push(12);
//     // test.push(0);
//     // test.push(9);
//     // test.push(-9);
//
//     // vector<int> nums {1,2,3,4,-8,-9};
//     vector<int> nums{-1, -2, -3, -4};
//     // vector<int> nums {-1,-2,-3};
//     Solution sl;
//     cout << sl.maximumProduct(nums) << endl;
//     return 0;
// }
