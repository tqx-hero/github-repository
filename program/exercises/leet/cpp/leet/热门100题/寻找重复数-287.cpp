/**
 * 287. 寻找重复数
中等
相关标签
premium lock icon
相关企业
给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。

假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。

你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。

 

示例 1：

输入：nums = [1,3,4,2,2]
输出：2
示例 2：

输入：nums = [3,1,3,4,2]
输出：3
示例 3 :

输入：nums = [3,3,3,3,3]
输出：3
 

 

提示：

1 <= n <= 105
nums.length == n + 1
1 <= nums[i] <= n
nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次
 

进阶：

如何证明 nums 中至少存在一个重复的数字?
你可以设计一个线性级时间复杂度 O(n) 的解决方案吗？
 */
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
//1、排序，遍历取出重复数
// class Solution {
// public:
//     int findDuplicate(vector<int>& nums) {
//         sort(nums.begin(),nums.end());
//         int i;
//         for(i=1;i<nums.size() && nums[i] != nums[i-1];i++);
//         return nums[i];
//     }
// };
//1~n有n个数，数组长度为n+1，并且范围在这个区间，数从1开始，所以可以以该数组作为哈希表，0号位置空出来了，可以作为哨兵位置
//迭代把哨兵位置的值放入对应的数组下标，在放入之前，判断对应下标的数是否与哨兵位置的数相同，不相同则交换，继续循环
//直到找到一个数值相同的，返回
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        while (nums[0] != nums[nums[0]])
            swap(nums[0],nums[nums[0]]);
        return nums[0];
    }
};

// int main(){
//     return 0;
// }