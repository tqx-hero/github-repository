/**
 * 338. 比特位计数
简单
相关标签
premium lock icon
相关企业
提示
给你一个整数 n ，对于 0 <= i <= n 中的每个 i ，计算其二进制表示中 1 的个数 ，返回一个长度为 n + 1 的数组 ans 作为答案。

不要使用内置函数来解决（例如，C++ 中的 __builtin_popcount）。

 

示例 1：

输入：n = 2
输出：[0,1,1]
解释：
0 --> 0
1 --> 1
2 --> 10
示例 2：

输入：n = 5
输出：[0,1,1,2,1,2]
解释：
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101
 

提示：

0 <= n <= 105
 

进阶：

很容易就能实现时间复杂度为 O(n log n) 的解决方案，你可以在线性时间复杂度 O(n) 内用一趟扫描解决此问题吗？
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//0-2^0：个数 0,1
//[2^1 - 2^2) 个数 为 1, 2
//[2^2 ~ 2^3) 个数: 1,2,2,3
//[2^3~2^4) 个数：1,2,2,3,2,3,3,4
//由此类推：
//从2的整数幂到下一个2的整数幂之间(左闭右开),1的个数都是上一个区间的个数，然后在拼接这个区间每个个数+1
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ret(n+1);
        ret[0] = 0;
        int i,sub_num = 1,next_num = sub_num << 1;
        for(i=1;i<=n;i++){
            if(i == next_num){
                ret[i] =1;
                sub_num =next_num;
                next_num <<=1;
            }else
                ret[i] = ret[i-sub_num]+1;
        }
        return ret;
    }
};

// int main(){
//     int n =5;
//     Solution sl;
//     const auto& vc = sl.countBits(n);
//     for_each(vc.begin(),vc.end(),[](int x){cout << x << " ";});
//     cout << endl;
//     return 0;
// }