/**
747. 至少是其他数字两倍的最大数
简单
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 nums ，其中总是存在 唯一的 一个最大整数 。

请你找出数组中的最大元素并检查它是否 至少是数组中每个其他数字的两倍 。如果是，则返回 最大元素的下标 ，否则返回 -1 。

 

示例 1：

输入：nums = [3,6,1,0]
输出：1
解释：6 是最大的整数，对于数组中的其他整数，6 至少是数组中其他元素的两倍。6 的下标是 1 ，所以返回 1 。
示例 2：

输入：nums = [1,2,3,4]
输出：-1
解释：4 没有超过 3 的两倍大，所以返回 -1 。
 

提示：

2 <= nums.length <= 50
0 <= nums[i] <= 100
nums 中的最大元素是唯一的
  */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int dominantIndex(vector<int>& nums) {
	int maxidx = std::max_element(nums.begin(),nums.end()) - nums.begin();
	int i,sz = static_cast<int>(nums.size()),maxval = nums[maxidx];
	for(i=0;i < sz;++i){
	    if(i == maxidx)
		continue;
	    if(maxval < (nums[i] << 1))
		return -1;
	}
	return maxidx;
    }
};

int main(){
    //nums = [3,6,1,0]
//    vector<int> nums{3,6,1,0};
    vector<int> nums{1,2,3,4};
    Solution sl;
    cout << sl.dominantIndex(nums) << endl;
    return 0;
}
