//
// Created by Administrator on 2026/8/11.
//
/**
* 外观数列
「外观数列」是一个数位字符串序列，由递归公式定义：

countAndSay(1) = "1"
countAndSay(n) 是 countAndSay(n-1) 的行程长度编码。
  

行程长度编码（RLE）是一种字符串压缩方法，其工作原理是通过将每个最大连续相同字符组替换为该组的长度后加上该字符本身。例如，要压缩字符串 "3322251" ，我们将 "33" 用 "23" 替换，将 "222" 用 "32" 替换，将 "5" 用 "15" 替换并将 "1" 用 "11" 替换。因此压缩后字符串变为 "23321511"。

给定一个整数 n ，返回 外观数列 的第 n 个元素。

示例 1：

输入：n = 4

输出："1211"

解释：

countAndSay(1) = "1"

countAndSay(2) = "1" 的行程长度编码 = "11"

countAndSay(3) = "11" 的行程长度编码 = "21"

countAndSay(4) = "21" 的行程长度编码 = "1211"

示例 2：

输入：n = 1

输出："1"

解释：

这是基本情况。

  

提示：

1 <= n <= 30
  

进阶：你能迭代解决该问题吗？

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xnpvdm/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <iostream>
#include <string>
using namespace std;

class Solution {
    string get_prev_seq(string str) {
        string ret;
        int cnt = 1, size = static_cast<int>(str.size());
        char cur = str[0];
        for (int i = 1; i < size; i++) {
            if (str[i] != cur) {
                ret.push_back(cnt + '0');
                ret.push_back(cur);
                cnt = 1;
                cur = str[i];
            } else
                cnt++;
        }
        ret.push_back(cnt + '0');
        ret.push_back(cur);
        return ret;
    }

public:
    string countAndSay(int n) {
        if (n == 1)
            return "1";
        return get_prev_seq(countAndSay(n - 1));
    }
};

// int main() {
//     Solution sl;
//     cout << sl.countAndSay(1) << endl;
//     return 0;
// }
