/**
 *697. 数组的度
简单
相关标签
premium lock icon
相关企业
提示
给定一个非空且只包含非负数的整数数组 nums，数组的 度 的定义是指数组里任一元素出现频数的最大值。

你的任务是在 nums 中找到与 nums 拥有相同大小的度的最短连续子数组，返回其长度。

 

示例 1：

输入：nums = [1,2,2,3,1]
输出：2
解释：
输入数组的度是 2 ，因为元素 1 和 2 的出现频数最大，均为 2 。
连续子数组里面拥有相同度的有如下所示：
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
最短连续子数组 [2, 2] 的长度为 2 ，所以返回 2 。
示例 2：

输入：nums = [1,2,2,3,1,4,2]
输出：6
解释：
数组的度是 3 ，因为元素 2 重复出现 3 次。
所以 [2,2,3,1,4,2] 是最短子数组，因此返回 6 。
 

提示：

nums.length 在 1 到 50,000 范围内。
nums[i] 是一个在 0 到 49,999 范围内的整数。
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <unordered_map>
using namespace std;
class Solution {

public:
    int findShortestSubArray(vector<int>& nums) {
	    size_t sz = nums.size();
	    unordered_map<int,tuple<int,int,int>> cache;
	    int i;
	    for(i=0;i < sz;++i){
		    auto& tp = cache[nums[i]];
		    if(get<0>(tp) ==0)
			    get<1>(tp) = i;
		    get<2>(tp) = i;
		    get<0>(tp)++;
	    }
	    int min_len = 0,max_cnt = 0;
	    for(auto& entry : cache){
		    auto& tp = entry.second;
		    if(get<0>(tp) == max_cnt)	//如果个数等于当前最大个数，比较区间哪个小
			    min_len = min(min_len,get<2>(tp) - get<1>(tp) + 1);
		    else if(get<0>(tp) > max_cnt){
			    min_len = get<2>(tp) - get<1>(tp) + 1;
			    max_cnt = get<0>(tp);
		    }
	    }
	    return min_len;
    }
};

int main(){
	vector<int> nums = {1,2,2,3,1};
	Solution sl;
	cout << sl.findShortestSubArray(nums) << endl;
	return 0;
}
