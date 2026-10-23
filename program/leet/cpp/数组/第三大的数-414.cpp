/**
 * 414. 第三大的数
简单
相关标签
premium lock icon
相关企业
给定一个整数数组 nums。

返回此数组中 第三大的数 。如果不存在，则返回数组中 最大 的数。



示例 1：

输入：[3, 2, 1]
输出：1
解释：第三大的数是 1 。
示例 2：

输入：[1, 2]
输出：2
解释：第三大的数不存在, 所以返回最大的数 2 。
示例 3：

输入：[2, 2, 3, 1]
输出：1
解释：注意，要求返回第三大的数，是指在所有不同数字中排第三大的数。
此例中存在两个值为 2 的数，它们都排第二。在所有不同数字中排第三大的数为 1 。


提示：

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1


进阶：你能设计一个时间复杂度 O(n) 的解决方案吗？
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <array>
#include <unordered_set>
using namespace std;

class Solution
{
    int quick_sort(vector<int> &true_nums, int left, int right, int target_index)
    {
        if (left == right)
            return true_nums[left];
        // 选主元
        array<int, 3> arr{left, left + (right - left) / 2, right};
        sort(arr.begin(), arr.end(), [&true_nums](const int x, const int y)
             { return true_nums[x] > true_nums[y]; });
        // 主元与第一个位置交换
        swap(true_nums[arr[1]], true_nums[left]);
        int size = static_cast<int>(true_nums.size()), tleft, tright, main_num = true_nums[left];
        for (tleft = left + 1, tright = size - 1; tleft <= tright; ++tleft, --tright)
        {
            for (; tleft <= tright && true_nums[tleft] > main_num; ++tleft)
                ;
            for (; tleft <= tright && true_nums[tright] < main_num; --tright)
                ;
            if (tleft > tright)
                break;
            swap(true_nums[tleft], true_nums[tright]);
        }
        // 放置主元位置
        swap(true_nums[left], true_nums[tright]);
        // 主元位置在tright，判断tright与target_index的大小
        int sub = target_index - tright;
        if (sub == 0)
            return true_nums[tright];
        // >0,要从tright后面区间查找
        if (sub > 0)
            return quick_sort(true_nums, tright + 1, right, target_index);
        else
            return quick_sort(true_nums, left, tright - 1, target_index);
    }

public:
    int thirdMax(vector<int> &nums)
    {
        // 剪枝
        unordered_set<int> hash_set(nums.begin(), nums.end());
        vector<int> true_nums(hash_set.begin(), hash_set.end());
        // 按照快排的思想，运用霍尔法选取主元，进行快排(按照由大到小逆序)
        // 每次快排后比较主元位置。
        // 如果主元位置是第三个，主元就是要找的数
        // 主元位置小于3，从主元后面的区间找第三个
        // 主元位置大于3，从主元前面区间找
        int size = static_cast<int>(true_nums.size());
        return size < 3 ? size == 1 ? true_nums[0] : max(true_nums[0], true_nums[1])
                        : quick_sort(true_nums, 0, size - 1, 2);
    }
};

// int main()
// {
//     // vector<int> nums{3, 2, 1};
//     // vector<int> nums{2, 1};
//     // vector<int> nums{2, 2, 3, 1, 4};
//     vector<int> nums{1, 2, 2, 5, 3, 5};
//     Solution sl;
//     cout << sl.thirdMax(nums) << endl;
//     return 0;
// }