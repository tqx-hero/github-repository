/**
 * 39. 组合总和
中等
相关标签
premium lock icon
相关企业
给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。

candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 target 的不同组合数少于 150 个。

 

示例 1：

输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
解释：
2 和 3 可以形成一组候选，2 + 2 + 3 = 7 。注意 2 可以使用多次。
7 也是一个候选， 7 = 7 。
仅有这两种组合。
示例 2：

输入: candidates = [2,3,5], target = 8
输出: [[2,2,2,2],[2,3,3],[3,5]]
示例 3：

输入: candidates = [2], target = 1
输出: []
 

提示：

1 <= candidates.length <= 30
2 <= candidates[i] <= 40
candidates 的所有元素 互不相同
1 <= target <= 40
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
    vector<vector<int>> ret;
    int candidate_size = 0;

    void dfs(vector<int>& candidates,int target,vector<int>& target_vc,int total_sum,
            int prev_idx){
        //当前统计数组的总和等于目标值，记录
        if(total_sum == target){
            ret.push_back(target_vc);
            return;
        }
        //当总和超过目标值，同样也需要返回
        if(total_sum > target)
            return;
        //总和小于目标值时继续往数组里面塞数字
        for(int i= prev_idx;i<candidate_size; ++i){
            //由于数字可重复使用，所以需要从当前下标往后尝试
            target_vc.push_back(candidates[i]);
            dfs(candidates,target,target_vc,total_sum + candidates[i],i);
            target_vc.pop_back();   //回溯，从下个下标再次递归
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        if(target == 1)
            return ret;
        candidate_size = static_cast<int>(candidates.size());
        vector<int> target_vc;
        dfs(candidates,target,target_vc,0,0);
        return ret;
    }
};

// int main(){
//     //candidates = [2,3,6,7], target = 7
//     vector<int> candidates{2,3,6,7};
//     int target = 7;
//     Solution sl;
//     const auto & evc = sl.combinationSum(candidates,target);
//     for_each(evc.begin(),evc.end(),[](const vector<int>& vc){
//         for_each(vc.begin(),vc.end(),[](const int x){cout << x << " ";});
//         cout << endl;
//     });
//     return 0;
// }