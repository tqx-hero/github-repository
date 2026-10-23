//
// Created by Administrator on 2026/8/4.
//
/**
* 2762. 不间断子数组
中等
相关标签
premium lock icon
相关企业
提示
给你一个下标从 0 开始的整数数组 nums 。nums 的一个子数组如果满足以下条件，那么它是 不间断 的：

i，i + 1 ，...，j  表示子数组中的下标。对于所有满足 i <= i1, i2 <= j 的下标对，都有 0 <= |nums[i1] - nums[i2]| <= 2 。
请你返回 不间断 子数组的总数目。

子数组是一个数组中一段连续 非空 的元素序列。



示例 1：

输入：nums = [5,4,2,4]
输出：8
解释：
大小为 1 的不间断子数组：[5], [4], [2], [4] 。
大小为 2 的不间断子数组：[5,4], [4,2], [2,4] 。
大小为 3 的不间断子数组：[4,2,4] 。
没有大小为 4 的不间断子数组。
不间断子数组的总数目为 4 + 3 + 1 = 8 。
除了这些以外，没有别的不间断子数组。
示例 2：

输入：nums = [1,2,3]
输出：6
解释：
大小为 1 的不间断子数组：[1], [2], [3] 。
大小为 2 的不间断子数组：[1,2], [2,3] 。
大小为 3 的不间断子数组：[1,2,3] 。
不间断子数组的总数目为 3 + 2 + 1 = 6 。


提示：

1 <= nums.length <= 105
1 <= nums[i] <= 109
 * @return
 */
#include <iostream>
#include <vector>
using namespace std;
/**
 * 用2个双端单调队列，一个单调递增，一个单调递减。分别存储当前窗口[left,right]的极值
 * 遍历集合，维护这2个队列头部的有效性。
 * 每个元素与这两个队列的头部进行计算：
 * 满足条件时，将当前元素分别添加到这两个队列尾部(需要比对，保持单调性)
 * 不满足条件，先统计left与right之间窗口大小，计算该窗口大小的连续数组数量，计入返回结果result。
 * 第二步就是left指针右移，减小区间范围，移动时同样需要判断队列头部的有效性。
 * 移动left指针当2个极值与当前元素计算差的绝对值均满足条件时，当前元素入队，继续进行之后的遍历，right++
 * 直到right指针到达末尾。
 * 最后还需要查看队列中是否还有未统计的数，统计完成计入result
 */
#include <deque>

class Solution {
public:
    long long continuousSubarrays(vector<int> &nums) {
        size_t size = nums.size();
        long long result = static_cast<long long>(size), subFactor = 0;
        if (size == 1)
            return result;
        int left = 0, right = 1;
        deque<int> maxDeque, minDeque;
        maxDeque.push_back(0);
        minDeque.push_back(0);
        for (; right < size; right++) {
            int num = nums[right];
            //如果极值不满足条件，需要先统计[left,right]这段区间的窗口大小
            if (abs(nums[maxDeque.front()] - num) > 2 || abs(nums[minDeque.front()] - num) > 2) {
                long long winSize = right - left;
                //为避免重复统计，超过2个数时才会统计
                if (winSize >= 2)
                    result += winSize * (winSize - 1) / 2 - subFactor;
                //left指针右移
                while (!maxDeque.empty()) {
                    int maxIdx = maxDeque.front();
                    int minIdx = minDeque.front();
                    int maxSubVal = abs(nums[maxIdx] - num);
                    int minSubVal = abs(nums[minIdx] - num);
                    if (maxSubVal > 2 && minSubVal > 2) {
                        left = max(maxIdx, minIdx) + 1;
                    } else if (maxSubVal > 2) {
                        left = maxIdx + 1;
                    } else if (minSubVal > 2) {
                        left = minIdx + 1;
                    } else
                        break;
                    //去掉2个单调队列头部小于left指针的数据
                    while (!maxDeque.empty() && maxDeque.front() < left)
                        maxDeque.pop_front();
                    while (!minDeque.empty() && minDeque.front() < left)
                        minDeque.pop_front();
                }
                //记录重复计算的区间，在下次统计时刨除
                long long repeatBound = right - left;
                subFactor = repeatBound * (repeatBound - 1) / 2;
            }
            updateMaxDeque(maxDeque, nums, right);
            updateMinDeque(minDeque, nums, right);
        }
        //如果还有未统计的，统计剩余的
        long long winSize;
        if ((winSize = (right - left)) >= 2)
            result += winSize * (winSize - 1) / 2 - subFactor;
        return result;
    }

private:
    void updateMinDeque(deque<int> &minDeque, vector<int> &nums, int index) {
        int num = nums[index];
        while (!minDeque.empty() && nums[minDeque.back()] >= num)
            minDeque.pop_back();
        minDeque.push_back(index);
    }

    void updateMaxDeque(deque<int> &maxDeque, vector<int> &nums, int index) {
        int num = nums[index];
        while (!maxDeque.empty() && nums[maxDeque.back()] <= num)
            maxDeque.pop_back();
        maxDeque.push_back(index);
    }
};

// int main() {
//     // vector<int> nums{1,2,3};
//     vector<int> nums{65, 66, 67, 66, 66, 65, 64, 65, 65, 64};
//     // vector<int> nums{5, 4, 2, 4};
//     Solution sl;
//     cout << sl.continuousSubarrays(nums) << endl;
//     return 0;
// }
