/**
 * 4. 寻找两个正序数组的中位数
已解答
困难
相关标签
premium lock icon
相关企业
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

算法的时间复杂度应该为 O(log (m+n)) 。

 

示例 1：

输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2
示例 2：

输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 

 

提示：

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
 */
#include <vector>
#include <iostream>
using namespace std;
//先考虑双指针解法
class Solution {
    double get_middle(vector<int>& nums,int sz){
        int idx= (sz-1)/2;
        if(sz % 2)
            return nums[idx];
        return 
            (nums[idx]+nums[idx+1]) /2.0;
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1_sz = static_cast<int>(nums1.size()),n2_sz = static_cast<int>(nums2.size()),
            size =n1_sz+n2_sz;
        if(!n1_sz)
            return get_middle(nums2,n2_sz);
        if(!n2_sz)
            return get_middle(nums1,n1_sz);
        int cur_idx = (size -1) /2 +1;
        int i=-1,n1_idx=0,n2_idx=0,left_val = 0,right_val = 0;
        while(i<cur_idx && n1_idx < n1_sz && n2_idx <n2_sz){
            left_val=right_val;
            if(nums1[n1_idx] <=nums2[n2_idx])
                right_val= nums1[n1_idx++];
            else 
                right_val= nums2[n2_idx++];
            i++;
        }
        //出现一个数组遍历完成的结果
        while(i< cur_idx){
            left_val = right_val;
            if(n1_idx < n1_sz)
               right_val= nums1[n1_idx++] ;
            else
                right_val=nums2[n2_idx++];
            i++;
        }
        if(size % 2 == 0)
            return (left_val + right_val) /2.0;
        else 
            return left_val;
    }
};

// int main(){
//     //nums1 = [1,3], nums2 = [2]
//     // vector<int> nums1{1,2},nums2{3,4};
//     vector<int> nums1{},nums2{3};
//     Solution sl;
//     cout << sl.findMedianSortedArrays(nums1,nums2) << endl;
//     return 0;
// }