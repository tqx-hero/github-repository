//
// Created by Administrator on 2026/8/11.
//
/**
* 最长公共前缀
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

  

示例 1：

输入：strs = ["flower","flow","flight"]
输出："fl"
示例 2：

输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。
  

提示：

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] 如果非空，则仅由小写英文字母组成



作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xnmav1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
    void update_prefix(string &prefix, string &str) {
        int pre_size = static_cast<int>(prefix.size()), min_size = min(
            static_cast<int>(str.size()), pre_size);
        int i = 0;
        for (; i < min_size && str[i] == prefix[i]; i++);
        if (i != pre_size)
            prefix.resize(i);
    }

public:
    string longestCommonPrefix(vector<string> &strs) {
        int size = static_cast<int>(strs.size());
        string prefix{strs[0]};
        if (size == 1)
            return prefix;
        for (int i = 1; i < size; i++) {
            update_prefix(prefix, strs[i]);
            if (prefix.empty())
                return prefix;
        }
        return prefix;
    }
};

// int main() {
//     vector<string> strs{"dog", "racecar", "car"};
//     // vector<string> strs{"flower", "flow", "flight"};
//     Solution sl;
//     cout << sl.longestCommonPrefix(strs) << endl;
//     return 0;
// }
