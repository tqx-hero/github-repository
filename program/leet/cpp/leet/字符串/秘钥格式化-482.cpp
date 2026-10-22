/**
 * 482. 密钥格式化
简单
相关标签
premium lock icon
相关企业
给定一个许可密钥字符串 s，仅由字母、数字字符和破折号组成。字符串由 n 个破折号分成 n + 1 组。你也会得到一个整数 k 。

我们想要重新格式化字符串 s，使每一组包含 k 个字符，除了第一组，它可以比 k 短，但仍然必须包含至少一个字符。此外，两组之间必须插入破折号，并且应该将所有小写字母转换为大写字母。

返回 重新格式化的许可密钥 。



示例 1：

输入：S = "5F3Z-2e-9-w", k = 4
输出："5F3Z-2E9W"
解释：字符串 S 被分成了两个部分，每部分 4 个字符；
     注意，两个额外的破折号需要删掉。
示例 2：

输入：S = "2-5g-3-J", k = 2
输出："2-5G-3J"
解释：字符串 S 被分成了 3 个部分，按照前面的规则描述，第一部分的字符可以少于给定的数量，其余部分皆为 2 个字符。


提示:

1 <= s.length <= 105
s 只包含字母、数字和破折号 '-'.
1 <= k <= 104
 */
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution
{
public:
    string licenseKeyFormatting(string s, int k)
    {
        int char_count = 0;
        for (auto ch : s)
            if (ch != '-')
                char_count++;
        if (char_count == 0)
            return string{};
        int ret_size = char_count + static_cast<int>(std::ceil(char_count * 1.0 / k)) - 1;
        string ret;
        ret.resize(ret_size);
        int mod = char_count % k, i = 0, j;
        size_t size = s.size();
        for (j = 0; j < mod; ++j)
        {
            while (s[i] == '-')
                i++;
            ret[j] = isdigit(s[i]) ? s[i] : toupper(s[i]);
            i++;
        }
        if (j != 0)
            ret[j++] = '-';
        for (; j < ret_size; ++j)
        {
            int n = k;
            for (; n > 0; n--)
            {
                while (s[i] == '-')
                    i++;
                ret[j] = isdigit(s[i]) ? s[i] : toupper(s[i]);
                j++;
                i++;
            }
            if (j < ret_size)
                ret[j] = '-';
        }
        return ret;
    }
};

// int main()
// {
//     // string s = "5F3Z-2e-9-w";
//     // int k = 4;
//     // string s = "2-5g-3-J";
//     // int k = 2;
//     // string s = "J";
//     // string s = "a-a-a-a-";
//     string s = "---";
//     int k = 1;
//     Solution sl;
//     cout << sl.licenseKeyFormatting(s, k) << endl;
//     return 0;
// }