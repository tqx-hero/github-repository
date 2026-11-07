/**
1005. K 次取反后最大化的数组和
简单
相关标签
premium lock icon
相关企业
给你一个整数数组 nums 和一个整数 k ，按以下方法修改该数组：

选择某个下标 i 并将 nums[i] 替换为 -nums[i] 。
重复这个过程恰好 k 次。可以多次选择同一个下标 i 。

以这种方式修改数组后，返回数组 可能的最大和 。

 

示例 1：

输入：nums = [4,2,3], k = 1
输出：5
解释：选择下标 1 ，nums 变为 [4,-2,3] 。
示例 2：

输入：nums = [3,-1,0,2], k = 3
输出：6
解释：选择下标 (1, 2, 2) ，nums 变为 [3,1,0,2] 。
示例 3：

输入：nums = [2,-3,-1,5,-4], k = 2
输出：13
解释：选择下标 (1, 4) ，nums 变为 [2,3,-1,5,4] 。
 

提示：

1 <= nums.length <= 104
-100 <= nums[i] <= 100
1 <= k <= 104
  */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//排序
//查看是否有负数、0
//如果有负数,那就将它取反
//遍历直到k减到0
//如果减到0之后还有负数或者减完负数k还有剩余，并且有0，直接计算数组之和
//如果还没减到0，没有负数与0了，那就查看剩余的k是否是偶数，偶数就能保证没有负数
//如果是奇数，那就往前把最后那个负数再减回去，最后计算和
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
	    int ret = 0;
	    std::sort(nums.begin(),nums.end());
	    //判断当前最小值是否为负数，如果为负数，就取反
	    int i;
	    size_t sz = nums.size();
	    for(i = 0;i < sz && k;++i){
		    int cur_num = nums[i];
		    //如果是负数，直接取反
		    if(cur_num < 0){
			    nums[i] = - cur_num;
			    k--;
			    continue;
		    }
		    if(cur_num > 0 && k % 2 != 0){ //如果最小值是正数，必然没有0
			    //剩余次数是奇数，需要把绝对值最小的取反
			    if(i == 0 || nums[i] <= nums[i - 1])
				    nums[i] = -cur_num;
			    else
				    nums[i - 1] = -nums[i - 1];
		    }
		    k = 0;
	    }
	    if(i == sz && k % 2) // 如果遍历结束，k是奇数，说明数组之前全部是负数，这种情况只需要把最后那个数取反
		    nums[sz - 1] = -nums[sz - 1];
	    for_each(nums.begin(),nums.end(),[&ret](const int num){
			    	ret += num;
			    });
	    return ret;
    }
};

int main(){
	vector<int> nums{2,-3,-1,5,-4};
	int k = 2;
	Solution sl;
	cout << sl.largestSumAfterKNegations(nums,k) << endl;
	return 0;
}
