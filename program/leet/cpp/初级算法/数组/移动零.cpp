//
// Created by Administrator on 2026/8/9.
//
/**
* 移动零
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
请注意 ，必须在不复制数组的情况下原地对数组进行操作。 
示例 1:
输入: nums = [0,1,0,3,12]
输出: [1,3,12,0,0]
示例 2:
输入: nums = [0]
输出: [0] 
提示:
• 1 <= nums.length <= 104
• -231 <= nums[i] <= 231 - 1 
进阶：你能尽量减少完成的操作次数吗？
 * @return
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int> &nums) {
        int size = static_cast<int>(nums.size());
        if (size == 1)
            return;
        //遍历查看有多少个0
        int zero_count = 0, first_index = -1, i;
        for (i = 0; i < size; i++) {
            if (!nums[i]) {
                zero_count++;
                if (first_index == -1)
                    first_index = i;
            }
        }
        if (!zero_count || zero_count == size)
            return;
        int left = first_index, right = left + 1;
        for (; right < size; right++) {
            int nm;
            if ((nm = nums[right]))
                nums[left++] = nm;
        }
        for (; left < size; left++)
            nums[left] = 0;
    }
};

// int main() {
//     vector<int> nums{0, 1, 0, 3, 12};
//     Solution sl;
//     sl.moveZeroes(nums);
//     std::for_each(nums.begin(), nums.end(), [](const int x) { cout << x << endl; });
//     return 0;
// }
