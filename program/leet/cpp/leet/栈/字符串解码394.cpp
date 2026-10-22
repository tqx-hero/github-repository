//
// Created by Administrator on 2026/7/25.
//
/**
* 394. 字符串解码
中等
相关标签
premium lock icon
相关企业
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

测试用例保证输出的长度不会超过 105。



示例 1：

输入：s = "3[a]2[bc]"
输出："aaabcbc"
示例 2：

输入：s = "3[a2[c]]"
输出："accaccacc"
示例 3：

输入：s = "2[abc]3[cd]ef"
输出："abcabccdcdcdef"
示例 4：

输入：s = "abc3[cd]xyz"
输出："abccdcdcdxyz"


提示：

1 <= s.length <= 30
s 由小写英文字母、数字和方括号 '[]' 组成
s 保证是一个 有效 的输入。
s 中所有整数的取值范围为 [1, 300]
 * @return
 */
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<int> countStack;
        vector<string> stringStack;
        int num = 0;
        for (char &ch: s) {
            //如果是数字，读取并转化成数字
            if (ch >= '0' && ch <= '9') {
                num = num * 10 + (ch - '0');
                continue;
            }
            //如果是[，先把之前可能收集到的数字放入栈内
            if (ch == '[') {
                countStack.push(num);
                num = 0;
            }
            string added{""};
            //如果是右方括号，需要弹栈，将字符串个数统计出来
            if (ch == ']') {
                string top;
                do {
                    top = stringStack.back();
                    stringStack.pop_back();
                    if (top == "[")
                        break;
                    added += top;
                } while (true);
                int count = countStack.top();
                countStack.pop();
                added = count == 1 ? added : mulString(added, count);
            } else
                added = ch;
            //如果都是字符的话，把它们转成字符串放入栈内
            stringStack.push_back(added);
        }
        string ret;
        for (string &str: stringStack) {
            std::reverse(str.begin(), str.end());
            ret += str;
        }
        return ret;
    }

private:
    string mulString(const string &str, int cnt) {
        string ret;
        ret.reserve(str.length() * cnt);
        while (cnt--) {
            ret += str;
        }
        return ret;
    }
};

// int main() {
//     //"3[z]2[2[y]pq4[2[jk]e1[f]]]ef"
//     string s = "3[z]2[2[y]pq4[2[jk]e1[f]]]ef";
//     // string s = "abc3[cd]xyz";
//     // string s = "2[abc]3[cd]ef";
//     // string s = "3[a2[c]]";
//     // string s = "3[a]2[bc]";
//     Solution sl;
//     cout << sl.decodeString(s) << endl;
//     return 0;
// }
