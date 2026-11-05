/**
961. 在长度 2N 的数组中找出重复 N 次的元素
尝试过
简单
相关标签
premium lock icon
相关企业
给你一个整数数组 nums ，该数组具有以下属性：

nums.length == 2 * n.
nums 包含 n + 1 个 不同的 元素，其中 n 个值在数组中出现 恰好一次。
nums 中恰有一个元素重复 n 次
找出并返回重复了 n 次的那个元素。

 

示例 1：

输入：nums = [1,2,3,3]
输出：3
示例 2：

输入：nums = [2,1,2,5,3,2]
输出：2
示例 3：

输入：nums = [5,1,5,2,5,3,5,4]
输出：5
 

提示：

2 <= n <= 5000
nums.length == 2 * n
0 <= nums[i] <= 104
nums 由 n + 1 个 不同的 元素组成，且其中一个元素恰好重复 n 次
  */
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
	    unordered_set<int> cache;
	    for(auto& num : nums){
		    if(cache.count(num))
			    return num;
		    cache.emplace(num);
	    }
	    return 0;
    }
};

int main(){
	return 0;
}
