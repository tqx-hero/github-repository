//
// Created by Administrator on 2026/8/3.
//
/**
* LCR 183. 望远镜中最高的海拔
困难
相关标签
premium lock icon
相关企业
科技馆内有一台虚拟观景望远镜，它可以用来观测特定纬度地区的地形情况。该纬度的海拔数据记于数组 heights ，其中 heights[i] 表示对应位置的海拔高度。请找出并返回望远镜视野范围 limit 内，可以观测到的最高海拔值。

示例 1：

输入：heights = [14,2,27,-5,28,13,39], limit = 3
输出：[27,27,28,28,39]
解释：
  滑动窗口的位置                最大值
---------------               -----
[14 2 27] -5 28 13 39          27
14 [2 27 -5] 28 13 39          27
14 2 [27 -5 28] 13 39          28
14 2 27 [-5 28 13] 39          28
14 2 27 -5 [28 13 39]          39


提示：

你可以假设输入总是有效的，在输入数组不为空的情况下：

1 <= limit <= heights.length
-10000 <= heights[i] <= 10000
 * @return
 */
#include <algorithm>
#include <deque>
#include <vector>
#include <iostream>
using namespace std;

/**
 * 维护一个单调递减双端队列，在保持窗口大小为limit的条件下，
 * 新添加的元素从队尾开始比对，大于等于队尾的就把队尾弹出，直到队列为空或严格小于队尾
 * 再入队。
 * 注意：队列中可存储元素在原集合中的下标来轻量化
 */
class Solution {
public:
    vector<int> maxAltitude(vector<int> &heights, int limit) {
        int size = static_cast<int>(heights.size());
        deque<int> idxDeque;
        vector<int> result;
        result.reserve(size + 1 - limit);
        int left, right;
        for (left = 0, right = 0; right < size; left++) {
            while (right - left < limit) {
                while (!idxDeque.empty() && heights[idxDeque.back()] <= heights[right])
                    idxDeque.pop_back();
                idxDeque.push_back(right++);
            }
            int idx = idxDeque.front();
            result.push_back(heights[idx]);
            if (idx <= left)
                idxDeque.pop_front();
        }
        return result;
    }
};

// int main() {
//     vector<int> height{14, 2, 27, -5, 28, 13, 39};
//     int limit = 3;
//     Solution sl;
//     const auto &result = sl.maxAltitude(height, limit);
//     std::for_each(result.begin(), result.end(), [](const int x) { cout << x << endl; });
//     return 0;
// }
