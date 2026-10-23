/*
46. 全排列
中等
相关标签
premium lock icon
相关企业
给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

 

示例 1：

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
示例 2：

输入：nums = [0,1]
输出：[[0,1],[1,0]]
示例 3：

输入：nums = [1]
输出：[[1]]
 

提示：

1 <= nums.length <= 6
-10 <= nums[i] <= 10
nums 中的所有整数 互不相同
*/
//TODO
#include <vector>
#include <iostream>
using namespace std;
class Solution {
    vector<vector<int>> ret;
    int num_size=0;
    void dfs(vector<int>&nums,vector<int>& vc,vector<int> &visited){
        //如果收集完一轮,统计结果
        if(vc.size() == num_size){
            ret.push_back(vc);
            return;
        }
        for(int i=0;i<num_size;++i){
            //如果当前节点还没加到数组，添加到数组
            if(!visited[i]){
                vc.push_back(nums[i]);
                //标记当前元素已加入数组
                visited[i] = 1;
                //递归放入其他元素
                dfs(nums,vc,visited);
                //走到这里已经收集完成一轮了，回溯
                visited[i] = 0;
                vc.pop_back();
            }
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        num_size = static_cast<int>(nums.size());
        vector<int> visited(num_size,0);
        vector<int> vc;
        vc.reserve(num_size);
        dfs(nums,vc,visited);
        return ret;
    }
};

// int main(){
//     vector<int> nums{1,2,3};
//     Solution sl;

//     return 0;
// }