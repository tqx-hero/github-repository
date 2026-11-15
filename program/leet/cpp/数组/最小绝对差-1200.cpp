/**
1200. 最小绝对差
简单
相关标签
premium lock icon
相关企业
提示
给你个整数数组 arr，其中每个元素都 不相同。

请你找到所有具有最小绝对差的元素对，并且按升序的顺序返回。

每对元素对 [a,b] 如下：

a , b 均为数组 arr 中的元素
a < b
b - a 等于 arr 中任意两个元素的最小绝对差
 

示例 1：

输入：arr = [4,2,1,3]
输出：[[1,2],[2,3],[3,4]]
示例 2：

输入：arr = [1,3,6,10,15]
输出：[[1,3]]
示例 3：

输入：arr = [3,8,-10,23,19,-4,-14,27]
输出：[[-14,-10],[19,23],[23,27]]
 

提示：

2 <= arr.length <= 10^5
-10^6 <= arr[i] <= 10^6
  */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        vector<vector<int>> ret;
        std::sort(arr.begin(),arr.end());
        unordered_map<int,vector<int>> cache;
        size_t size = arr.size();
        //遍历数组，并且计算出相邻2元素之间的差
        int minsub = INT_MAX;
        for(int i = 0;i < size - 1;++i){
            int cursub = arr[i + 1] - arr[i];
            if(cursub <= minsub){
                cache[cursub].push_back(i);
                minsub = cursub;
            }
        }
        auto& vc = cache[minsub];
        for(auto& idx : vc)
            ret.push_back(vector<int>{arr[idx],arr[idx + 1]});
        return ret;
    }
};

int main(){
    vector<int> arr{3,8,-10,23,19,-4,-14,27};
    Solution sl;
    const auto& vc = sl.minimumAbsDifference(arr);
    for(int i = 0;i < vc.size();++i)
        cout << vc[i][0] << " " << vc[i][1] << endl;
    return 0;
}
