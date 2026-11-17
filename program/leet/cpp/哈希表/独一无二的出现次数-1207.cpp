/**
1207. 独一无二的出现次数
简单
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 arr，如果每个数的出现次数都是独一无二的，就返回 true；否则返回 false。

 

示例 1：

输入：arr = [1,2,2,1,1,3]
输出：true
解释：在该数组中，1 出现了 3 次，2 出现了 2 次，3 只出现了 1 次。没有两个数的出现次数相同。
示例 2：

输入：arr = [1,2]
输出：false
示例 3：

输入：arr = [-3,0,1,-3,1,1,1,-3,10,0]
输出：true
 

提示：

1 <= arr.length <= 1000
-1000 <= arr[i] <= 1000
  */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> cache;
        for(auto& num : arr)
            ++cache[num];
        unordered_set<int> cnt_cache;
        for(auto& pair : cache)
            cnt_cache.emplace(pair.second);
        return cache.size() == cnt_cache.size();
    }
};

int main(){
    vector<int> arr{1,2,2,1,1,3};
    Solution sl;
    cout << sl.uniqueOccurrences(arr) << endl;
    exit(0);
}
