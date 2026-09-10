/**
 * 394. 字符串解码
已解答
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
 */
#include <string>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
class Solution {
    //生成字符串,并将字符串放到栈内
    void concat_str(stack<int>& cnt_stack,string& char_stack){
        //字符为],需要弹栈，直到弹出第一个[,获取这个字符串
        char top_ch;
        string cur_str;
        do{
            top_ch = char_stack.back();
            char_stack.pop_back();
            if(top_ch =='[')
                break;
            cur_str.push_back(top_ch);
        }
        while(true);
        int cnt = cnt_stack.top();
        cnt_stack.pop();
        //将倒着的字符串放入栈内,放cnt次
        int size = static_cast<int>(cur_str.size());
        while (cnt--)
            for(int i= size -1;i >= 0;--i)
                char_stack.push_back(cur_str[i]);
    }
public:
    string decodeString(string s) {
        stack<int> cnt_stack;
        string char_stack;
        int size =static_cast<int>(s.size());
        for(int i=0;i<size;++i){
            //如果字符是数字，需要把数字的子串转化为数字
            char ch;
            int num=0;
            while(isdigit((ch = s[i]))){
                num = num *10 + ch - '0';
                i++;
            }
            //如果统计的数字不为0，将它放入统计数字的栈内
            if(num)
                cnt_stack.push(num);
            //如果不是数字，判断是否为]，不是就入栈
            if(ch == ']')
                //字符为],需要弹栈，直到弹出第一个[,获取这个字符串
                concat_str(cnt_stack,char_stack);
            else
                char_stack.push_back(ch);
        }
        return char_stack;
    }
};

// int main(){
//     // string s = "3[a]2[bc]";
//     // string s = "2[abc]3[cd]ef";
//     string s = "3[a2[c]]";
//     Solution sl;
//     cout << "str:" << endl;
//     cout << (sl.decodeString(s) == "accaccacc") << endl;
//     return 0;
// }