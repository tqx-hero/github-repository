/**
 * 45. 跳跃游戏 II
中等
相关标签
premium lock icon
相关企业
给定一个长度为 n 的 0 索引整数数组 nums。初始位置在下标 0。

每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在索引 i 处，你可以跳转到任意 (i + j) 处：

0 <= j <= nums[i] 且
i + j < n
返回到达 n - 1 的最小跳跃次数。测试用例保证可以到达 n - 1。



示例 1:

输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
示例 2:

输入: nums = [2,3,0,1,4]
输出: 2


提示:

1 <= nums.length <= 104
0 <= nums[i] <= 1000
题目保证可以到达 n - 1
 */
#include <vector>
#include <iostream>
using namespace std;
// 从起始节点到能达到的最远距离之间的所有节点走的步数都相同
// 维护一个变量，记录所有节点能达到的最远下标
// 从起点到这个下标所有的节点在遍历时不增加步数，只有当到达原始的那个最远点时再增加步数，这样就只需要增加一步
class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int size = static_cast<int>(nums.size());
        int step = 0, end = 0, max_distinct = 0, i;
        for (i = 0; i < size - 1; ++i)
        {
            // 先更新每个下标的最远距离
            max_distinct = max(max_distinct, i + nums[i]);
            // 当下标到达原来记录的初始最远边界时，增加一步,并修改它的边界为当前的最远距离
            if (i == end || max_distinct == size - 1)
            {
                ++step;
                //可能出现提前退出的情况
                if (max_distinct == size - 1)
                    return step;
                end = max_distinct;
            }
        }
        return step;
    }
};

// int main()
// {
//     // vector<int> nums{2, 3, 1, 1, 4};
//     // vector<int> nums{2,3,0,1,4};
//     vector<int> nums{4, 1, 1, 3, 1, 1, 1};
//     Solution sl;
//     cout << sl.jump(nums) << endl;
//     return 0;
// }