/**
 * 22. 括号生成
中等
相关标签
premium lock icon
相关企业
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

 

示例 1：

输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
示例 2：

输入：n = 1
输出：["()"]
 

提示：

1 <= n <= 8
 */
#include <vector>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution {
    vector<string> ret;
    void build_str(string& str,int left_cnt,int right_cnt){
        //左右括号都放入完毕，统计生成的子串
        if(!left_cnt && !right_cnt){
            ret.push_back(str);
            return;
        }
        //还有没放入的括号，先放可能存在的左括号
        if(left_cnt){
            str.push_back('(');
            //处理放入左括号后的后续情况
            build_str(str,left_cnt-1,right_cnt);
            //回溯，将左括号拿出来，还原初始状态
            str.pop_back();
        }
        //处理完上述情况后，在处理能放入右括号的情况
        if(right_cnt > left_cnt){
            str.push_back(')');
            build_str(str,left_cnt,right_cnt-1);
            str.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        string str;
        str.reserve(n << 1);
        build_str(str,n,n);
        return ret;
    }
};

// int main(){
//     return 0;
// }