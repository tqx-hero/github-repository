/**
 * 405. 数字转换为十六进制数
简单
相关标签
premium lock icon
相关企业
给定一个整数，编写一个算法将这个数转换为十六进制数。对于负整数，我们通常使用 补码运算 方法。

答案字符串中的所有字母都应该是小写字符，并且除了 0 本身之外，答案中不应该有任何前置零。

注意: 不允许使用任何由库提供的将数字直接转换或格式化为十六进制的方法来解决这个问题。



示例 1：

输入：num = 26
输出："1a"
示例 2：

输入：num = -1
输出："ffffffff"


提示：

-231 <= num <= 231 - 1
 */
#include <string>
#include <iostream>
#include <array>
using namespace std;

class Solution
{
public:
    string toHex(int num)
    {
        // 位运算。以四位为单位与f进行与运算，获得值转化为字符串
        // 需要剔除前导0，所以从最高位28~31进行位运算，不为0开始填入
        if (num == 0)
            return string{"0"};
        array<char, 16> hash_map{
            '0', '1', '2', '3',
            '4', '5', '6', '7',
            '8', '9', 'a', 'b',
            'c', 'd', 'e', 'f'};
        string ret;
        int umask = 0xf, i, cur_num;
        // 找到第一个不为0的最高位
        for (i = 28; i >= 0 && (cur_num = (num >> i) & umask) == 0; i -= 4)
            ;
        ret.push_back(hash_map[cur_num]);
        for (i -= 4; i >= 0; i -= 4)
            ret.push_back(hash_map[(num >> i) & umask]);
        return ret;
    }
};

// int main()
// {
//     // int num = -1;
//     int num = 26;
//     Solution sl;
//     cout << sl.toHex(num) << endl;
//     return 0;
// }