/**
 * 33. 搜索旋转排序数组
中等
相关标签
premium lock icon
相关企业
整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 向左旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 下标 3 上向左旋转后可能变为 [4,5,6,7,0,1,2] 。

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。

你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。

 

示例 1：

输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4
示例 2：

输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1
示例 3：

输入：nums = [1], target = 0
输出：-1
 

提示：

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
nums 中的每个值都 独一无二
题目数据保证 nums 在预先未知的某个下标上进行了旋转
-104 <= target <= 104
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
    int binary_search_target(vector<int>&nums,int left,int right,int target){
        if(left > right)
            return -1;
        //如果左边界小于右边界，该区间严格单调递增，直接二分查找是否存在
        if(nums[left] < nums[right]){
            auto it =  lower_bound(nums.begin()+left,nums.begin()+right+1,target);
            if(it == nums.end() || *it != target)
                return -1;
            return static_cast<int>(it - nums.begin());
        }else{
            //左边界大于右边界，该区间有凹陷
            int mid = left + (right - left) /2;
            int mid_val = nums[mid],left_val = nums[left];
            if(mid_val == target)
                return mid;
            if((left_val > mid_val && (mid_val > target || left_val <= target))
                    ||
                    (left_val < mid_val && mid_val > target && left_val <= target))
                return binary_search_target(nums,left,mid-1,target);     
            return binary_search_target(nums,mid+1,right,target);
        }
    }
public:
    int search(vector<int>& nums, int target) {
        return binary_search_target(nums,0,nums.size()-1,target);
    }
};

// int main(){
//     //nums = [4,5,6,7,0,1,2], target = 0
//     vector<int> nums{4,5,6,7,0,1,2};
//     int target =0;
//     Solution sl;
//     cout << sl.search(nums,target) << endl;
//     return 0;
// }