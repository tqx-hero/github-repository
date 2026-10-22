//
// Created by Administrator on 2026/8/16.
//
/**
* 杨辉三角
给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。



  

示例 1:

输入: numRows = 5
输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
示例 2:

输入: numRows = 1
输出: [[1]]
  

提示:

1 <= numRows <= 30

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xncfnv/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > ret;
        ret.resize(numRows);
        ret[0] = {1};
        for (int i = 2; i <= numRows; i++) {
            vector<int> child_vec(i, 1), &prev_vec = ret[i - 2];
            int prev_size = static_cast<int>(prev_vec.size());
            if (prev_size > 1)
                for (int k = 1; k < prev_size; k++)
                    child_vec[k] = prev_vec[k - 1] + prev_vec[k];
            ret[i - 1] = child_vec;
        }
        return ret;
    }
};

// int main() {
//     int numRows = 5;
//     Solution sl;
//     const auto &vc = sl.generate(numRows);
//     std::for_each(vc.begin(), vc.end(),
//                   [](const vector<int> &vcs) {
//                       std::for_each(vcs.begin(), vcs.end(), [](const int x) { cout << x << " "; });
//                       cout << endl;
//                   });
//     return 0;
// }
