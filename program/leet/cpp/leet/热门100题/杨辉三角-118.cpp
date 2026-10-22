/**
 * 118. 杨辉三角
已解答
简单
相关标签
premium lock icon
相关企业
给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。



 

示例 1:

输入: numRows = 5
输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
示例 2:

输入: numRows = 1
输出: [[1]]
 

提示:

1 <= numRows <= 30
 */
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret;
        ret.push_back(vector<int>{1});
        int i;
        for(i=2;i <= numRows;++i){
            vector<int> row_vc(i);
            int left = 0,right = i-1;
            row_vc[left] = row_vc[right] =1;
            auto& prev_vc = ret.back();
            for(left++,right--;left <= right;++left,--right)
                row_vc[left] =row_vc[right] = prev_vc[left-1]+ prev_vc[left];
            ret.push_back(row_vc);
        }
        return ret;
    }
};

// int main(){
//     int numRows = 5;
//     Solution sl;
//     const auto& result = sl.generate(numRows);
//     for_each(result.begin(),result.end(),[](const vector<int>& vc){
//         for_each(vc.begin(),vc.end(),[](const int x){cout << x <<" ";});
//         cout << endl;
//     });
//     return 0;
// }