/**
 * 263. 丑数
尝试过
简单
相关标签
premium lock icon
相关企业
丑数 就是只包含质因数 2、3 和 5 的 正 整数。

给你一个整数 n ，请你判断 n 是否为 丑数 。如果是，返回 true ；否则，返回 false 。

 

示例 1：

输入：n = 6
输出：true
解释：6 = 2 × 3
示例 2：

输入：n = 1
输出：true
解释：1 没有质因数。
示例 3：

输入：n = 14
输出：false
解释：14 不是丑数，因为它包含了另外一个质因数 7 。
 

提示：

-231 <= n <= 231 - 1
 */

class Solution {
public:
    bool isUgly(int n) {
        if(n <=0)
            return false;
        while(n%2 == 0) n/=2;
        while(n%3 == 0) n/=3;
        while(n%5 == 0) n/=5;
        return n ==1;
    }
};

// int main(){
//     return 0;
// }