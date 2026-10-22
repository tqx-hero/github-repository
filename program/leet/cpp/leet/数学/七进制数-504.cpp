/**
 * 504. 七进制数
简单
相关标签
premium lock icon
相关企业
给定一个整数 num，将其转化为 7 进制，并以字符串形式输出。



示例 1:

输入: num = 100
输出: "202"
示例 2:

输入: num = -7
输出: "-10"


提示：

-107 <= num <= 107
 */
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

class Solution
{
public:
    string convertToBase7(int num)
    {
        if (num == 0)
            return string{'0'};
        string ret;
        int remain = abs(num);
        while (remain)
        {
            ret.push_back(remain % 7 + '0');
            remain /= 7;
        }
        if (num < 0)
            ret.push_back('-');
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

// int main()
// {
//     return 0;
// }