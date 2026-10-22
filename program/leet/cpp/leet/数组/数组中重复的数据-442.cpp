/**
 * 442. 数组中重复的数据
中等
相关标签
premium lock icon
相关企业
给你一个长度为 n 的整数数组 nums ，其中 nums 的所有整数都在范围 [1, n] 内，且每个整数出现 最多两次 。请你找出所有出现 两次 的整数，并以数组形式返回。

你必须设计并实现一个时间复杂度为 O(n) 且仅使用常量额外空间（不包括存储输出所需的空间）的算法解决此问题。



示例 1：

输入：nums = [4,3,2,7,8,2,3,1]
输出：[2,3]
示例 2：

输入：nums = [1,1,2]
输出：[1]
示例 3：

输入：nums = [1]
输出：[]


提示：

n == nums.length
1 <= n <= 105
1 <= nums[i] <= n
nums 中的每个元素出现 一次 或 两次
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// TODO
class Solution
{
public:
    vector<int> findDuplicates(vector<int> &nums)
    {
        vector<int> ret;
        int i, size = static_cast<int>(nums.size());
        for (i = 0; i < size; ++i)
        {
            int num = nums[i],j=i;
            if (num == 0 || num % size == i)
                continue;
            //  开始将num放到数组的对应下标
            // 当num取模size的下标所在值不为0时，表示这个坑还没被填
            while (true)
            {
                // 将j的下标值，也就是num先前所在的下标值设置为0
                if(nums[j] % size != j)
                    nums[j] = 0;
                j = num % size;
                // 拿出要放入的下标所在值
                int temp = nums[j];
                // 如果temp与num相同，说明已经有num放入
                if (temp == num)
                {
                    ret.push_back(num);
                    break;
                }
                // 将num放入这个下标
                nums[j] = num;
                if (temp == 0)
                    // 如果取出的值为0，说明这个坑之前已经拿出该值，i++
                    break;
                // 如果temp不为0且不等于num，继续安置temp
                num = temp;
            }
        }
        return ret;
    }
};

// int main()
// {
//     // vector<int> nums{4, 3, 2, 7, 8, 2, 3, 1};
//     // vector<int> nums{1,1,2};
//     vector<int> nums{1};
//     Solution sl;
//     const auto &vc = sl.findDuplicates(nums);
//     for_each(vc.begin(), vc.end(), [](const int x)
//              { cout << x << " "; });
//     cout << endl;
//     return 0;
// }