/*
17. 电话号码的字母组合
中等
相关标签
premium lock icon
相关企业
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。



 

示例 1：

输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
示例 2：

输入：digits = "2"
输出：["a","b","c"]
 

提示：

1 <= digits.length <= 4
digits[i] 是范围 ['2', '9'] 的一个数字。
*/
#include <vector>
#include <string>
#include <array>
#include <iostream>
using namespace std;

class Solution {
    vector<string> ret;
    int str_size = 0;
    array<string,8> hash_map{
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz"
    };

    void dfs(string& dights,string& str,int prev_idx){
        if(str.size() == str_size){
            ret.push_back(str);
            return;
        }
        for(int i = prev_idx+1 ; i<str_size ; ++i ){
            string sub_str = hash_map[dights[i] - '2'];
            for(char ch : sub_str){
                str.push_back(ch);
                dfs(dights,str,i);
                str.pop_back();
            }
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        str_size = static_cast<int>(digits.size());
        string str;
        str.reserve(str_size);
        dfs(digits,str,-1);
        return ret;
    }
};

// int main(){
//     return 0;
// }