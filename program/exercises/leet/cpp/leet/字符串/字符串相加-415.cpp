/**
 * 415. 字符串相加
简单
相关标签
premium lock icon
相关企业
给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和并同样以字符串形式返回。

你不能使用任何內建的用于处理大整数的库（比如 BigInteger）， 也不能直接将输入的字符串转换为整数形式。



示例 1：

输入：num1 = "11", num2 = "123"
输出："134"
示例 2：

输入：num1 = "456", num2 = "77"
输出："533"
示例 3：

输入：num1 = "0", num2 = "0"
输出："0"




提示：

1 <= num1.length, num2.length <= 104
num1 和num2 都只包含数字 0-9
num1 和num2 都不包含任何前导零
 */
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
public:
    string addStrings(string num1, string num2)
    {
        int remain = 0, i, j, n1_size = static_cast<int>(num1.size()), n2_size = static_cast<int>(num2.size());
        string ret;
        for (i = n1_size - 1, j = n2_size - 1; i >= 0 || j >= 0 || remain; i--, j--)
        {
            int sum = remain;
            if (i >= 0)
                sum += num1[i] - '0';
            if (j >= 0)
                sum += num2[j] - '0';
            if (sum > 9)
                remain = 1;
            else
                remain = 0;
            ret.push_back(sum % 10 + '0');
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

// int main()
// {
//     // string num1 = "11", num2 = "123";
//     string num1 = "456", num2 = "77";
//     Solution sl;
//     cout << sl.addStrings(num1, num2) << endl;
//     return 0;
// }