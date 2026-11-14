/**
1175. 质数排列
简单
相关标签
premium lock icon
相关企业
提示
请你帮忙给从 1 到 n 的数设计排列方案，使得所有的「质数」都应该被放在「质数索引」（索引从 1 开始）上；你需要返回可能的方案总数。

让我们一起来回顾一下「质数」：质数一定是大于 1 的，并且不能用两个小于它的正整数的乘积来表示。

由于答案可能会很大，所以请你返回答案 模 mod 10^9 + 7 之后的结果即可。

 

示例 1：

输入：n = 5
输出：12
解释：举个例子，[1,2,5,4,3] 是一个有效的排列，但 [5,2,3,4,1] 不是，因为在第二种情况里质数 5 被错误地放在索引为 1 的位置上。
示例 2：

输入：n = 100
输出：682289015
 

提示：

1 <= n <= 100
  */
#include <iostream>
#include <unordered_set>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

class Solution {
public:
    int numPrimeArrangements(int n) {
        if(n == 1)
            return 1;
        vector<int> arr(n + 1,-1);
        int count = 0;
        int i,j;
        for(i = 2;i <= n;++i){
            if(arr[i] == -1)
                arr[i] = 0;
            for(j = 2;j <= i && i * j <= n;++j)
                arr[i * j] = 1; //获取不是质数的数
        }
        //统计质数个数
        for(i = 2;i <= n;++i){
            if(arr[i] == 0)
                count++;
        }
        unsigned long long  ret = 1;
        for(i = 2;i <= count;++i){
            ret *= i;
            if(ret >= INT_MAX)
                ret %= (static_cast<unsigned long long>(pow(10,9)) + 7);
        }
        for(i = 2;i <= n - count;++i){
            ret *= i;
            if(ret >= INT_MAX)
                ret %= (static_cast<unsigned long long>(pow(10,9)) + 7);
        }
        if(ret >= INT_MAX)
            ret %= (static_cast<unsigned long long>(pow(10,9)) + 7);
        return static_cast<int>(ret);
    }
};

int main(){
    int n = 100;
    Solution sl;
    cout << sl.numPrimeArrangements(n) << endl;
    exit(0);
}
