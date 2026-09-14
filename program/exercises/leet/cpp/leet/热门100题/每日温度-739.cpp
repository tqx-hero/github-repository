/**
 * 739. 每日温度
已解答
中等
相关标签
premium lock icon
相关企业
提示
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

 

示例 1:

输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
示例 2:

输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]
示例 3:

输入: temperatures = [30,60,90]
输出: [1,1,0]
 

提示：

1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100
 */
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<vector<int>::reverse_iterator> stk;
        vector<int> ret(temperatures.size());
        vector<int>::reverse_iterator it,end_it = temperatures.rend(),cur_it = ret.rbegin(),top_it;
        for(it = temperatures.rbegin();it != end_it;++it,++cur_it){
            while(!stk.empty() && *(top_it = stk.top()) <= *it)
                stk.pop();
            *cur_it = stk.empty() ? 0 : static_cast<int>(it - top_it);
            stk.push(it);
        }
        return ret;
    }
};

// int main(){
//     vector<int> temperatures = {73,74,75,71,69,72,76,73};
//     Solution sl;
//     const auto& vc= sl.dailyTemperatures(temperatures);
//     for_each(vc.begin(),vc.end(),[](const int x){cout << x << " ";});
//     cout << endl;
//     return 0;
// }