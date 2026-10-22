/**
 * 347. 前 K 个高频元素
中等
相关标签
premium lock icon
相关企业
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

 

示例 1：

输入：nums = [1,1,1,2,2,3], k = 2

输出：[1,2]

示例 2：

输入：nums = [1], k = 1

输出：[1]

示例 3：

输入：nums = [1,2,1,2,1,2,3,1,3,2], k = 2

输出：[1,2]

 

提示：

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k 的取值范围是 [1, 数组中不相同的元素的个数]
题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的
 

进阶：你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;
//先对数组进行排序
//用红黑树map保存词频，键值对为: <词频(int)，等于该词频的元素集合(vector)>
//前k个，就遍历红黑树，直到取出前k个vector内的值为止
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if(nums.size() ==1 )
            return nums;
        unordered_map<int,int> value_cnt;
        map<int,vector<int>,greater<int>> tree_map;
        for(auto num : nums)
            value_cnt[num]++;
        for(auto& pr : value_cnt)
            //根据次数放入红黑树相应的节点
            tree_map[pr.second].push_back(pr.first);
        vector<int> ret;
        ret.reserve(k);
        //遍历红黑树，找出前k个值
        for(auto& tr: tree_map){
            if(!k)
                break;
            auto& vc = tr.second;
            ret.insert(ret.begin(),vc.begin(),vc.end());
            k -= vc.size();
        }
        return ret;
    }
};

// int main(){
//     vector<int> nums = {1,1,1,2,2,3};
//     int  k = 2;
//     Solution sl;
//     const auto & vc = sl.topKFrequent(nums,k);
//     for_each(vc.begin(),vc.end(),[](int x){cout << x << " ";});
//     cout << endl;
//     return 0;
// }