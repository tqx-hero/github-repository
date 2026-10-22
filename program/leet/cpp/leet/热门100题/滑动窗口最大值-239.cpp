//
// Created by Administrator on 2026/8/31.
//
/**
* 239. 滑动窗口最大值
已解答
困难
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回 滑动窗口中的最大值 。



示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：

输入：nums = [1], k = 1
输出：[1]


提示：

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
 * @return
 */
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        //单调递减队列，维护当前的最大值，新元素添加之前与队尾比较大小，超过队尾的就不需要保留队尾
        //一直到队列为空，或者队尾大于当前值
        //将当前值放入队尾
        //每次遍历先查看队头元素下标是否小于当前下标，小于就出队
        deque<int> ordered_queue;
        int size = static_cast<int>(nums.size());
        vector<int> ret;
        ret.reserve(size - k + 1);
        for (int left = 0, right = 0; right < size;) {
            //填充窗口
            while (right - left <= k - 1) {
                while (!ordered_queue.empty() && nums[ordered_queue.back()] <= nums[right])
                    ordered_queue.pop_back();
                ordered_queue.push_back(right++);
            }
            //记录最大值
            ret.push_back(nums[ordered_queue.front()]);
            //left指针移动，缩小窗口范围,同时还需要将队头的小于left下标出队
            while (!ordered_queue.empty() && ordered_queue.front() <= left)
                ordered_queue.pop_front();
            left++;
        }
        return ret;
    }
};

// int main() {
//     vector<int> nums{1, 3, -1, -3, 5, 3, 6, 7};
//     int k = 3;
//     Solution sl;
//     const auto &ret = sl.maxSlidingWindow(nums, k);
//     for_each(ret.begin(), ret.end(), [](const int x) { cout << x << " "; });
//     cout << endl;
//     return 0;
// }
