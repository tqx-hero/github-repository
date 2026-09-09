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

    int size =0;

    int get_index(vector<int> &visited){
        int i =0;
        for(;i<size && visited[i];++i);
        return i;
    }

    void dfs(vector<int>&nums,vector<int>& vc,vector<int> &visited,int i,int& sum){
        vc.push_back(nums[i]);
        visited[i] = 1;
        ++sum;
        //查找后面第一个未访问的节点
        if(sum == size)
            return;
        dfs(nums,vc,visited,get_index(visited),sum);
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        size = static_cast<int>(nums.size());
        vector<vector<int>> ret;
        for(int i=0;i<size;++i){
            int sum = 0;
            vector<int> visited(size,0);
            vector<int> vc(size);
            dfs(nums,vc,visited,i,sum);
            ret.push_back(vc);
        }
        return ret;
    }
};

// int main(){
//     return 0;
// }