/**
 * 55. 跳跃游戏
中等
相关标签
premium lock icon
相关企业
给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。



示例 1：

输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
示例 2：

输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。


提示：

1 <= nums.length <= 104
0 <= nums[i] <= 105
 */
#include <vector>
#include <iostream>
#include <unordered_set>
#include <set>
using namespace std;
// 贪心往前跳，每次跳完更新最远距离，直到跳过终点或者跳不动为止
class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int size = static_cast<int>(nums.size()), i, max_distinct = 0;
        for (i = 0; i <= size - 1; ++i)
        {
            max_distinct = max(max_distinct, i + nums[i]);
            if (max_distinct >= size - 1)
                return true;
            if (max_distinct == i)
                return false;
        }
        return false;
    }
};

// class Solution
// {
// public:
//     bool canJump(vector<int> &nums)
//     {
//         int size = static_cast<int>(nums.size()), i;
//         if (!nums[0])
//             return size == 1;
//         set<int> can_reach_idx_set;
//         // 统计可达的点，放入红黑树
//         can_reach_idx_set.emplace(size-1);
//         for (i = size - 2; i >= 0; i--)
//         {
//             if(!nums[i])
//                 continue;
//             int max_reach_idx = min(i+nums[i],size-1);
//             //非0时，计算到达的区间为[i+1,i+nums[i]]
//             //查询这个区间内是否有下标存在于红黑树，存在则可达，放入红黑树
//             auto it = can_reach_idx_set.lower_bound(max_reach_idx);
//             //如果存在，
//             if(*it == max_reach_idx || (--it) != --can_reach_idx_set.begin())
//                 can_reach_idx_set.emplace(i);
//         }
//         // 最后查看起点是否存在于不可达集合
//         return can_reach_idx_set.count(0);
//     }
// };

// int main()
// {
//     // vector<int> nums{2, 3, 1, 1, 4};
//     // vector<int> nums{3, 2, 1, 0, 4};
//     vector<int> nums{0};
//     // vector<int> nums{2,5,0,0};
//     // vector<int> nums{3,0,8,2,0,0,1};
//     Solution sl;
//     cout << sl.canJump(nums) << endl;
//     return 0;
// }