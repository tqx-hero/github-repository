/**
 * 78. 子集
中等
相关标签
premium lock icon
相关企业
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

 

示例 1：

输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
示例 2：

输入：nums = [0]
输出：[[],[0]]
 

提示：

1 <= nums.length <= 10
-10 <= nums[i] <= 10
nums 中的所有元素 互不相同
 */
#include <vector>
#include <iostream>
using namespace std;
class Solution {
    vector<vector<int>> ret;
    int total_size=0;
    void dfs(vector<int>& nums,vector<int>& sub_vc,int size,int prev_index){
        //如果要求的数组长度满足要求，记录到结果，返回进行下一轮收集
        if(sub_vc.size() == size){
            ret.push_back(sub_vc);
            return;
        }
        //不满足要求就遍历往数组添加元素
        for(int i=prev_index +1;i < total_size;++i){
            sub_vc.push_back(nums[i]);
            dfs(nums,sub_vc,size,i);
            sub_vc.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        total_size = static_cast<int>(nums.size());
        vector<int> sub_vc;
        for(int i=0; i <= total_size;++i)
            dfs(nums,sub_vc,i,-1);
        return ret;
    }
};

// int main(){
//     return 0;
// }