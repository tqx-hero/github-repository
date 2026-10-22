/**
 * 131. 分割回文串
中等
相关标签
premium lock icon
相关企业
给你一个字符串 s，请你将 s 分割成一些 子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。

 

示例 1：

输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]
示例 2：

输入：s = "a"
输出：[["a"]]
 

提示：

1 <= s.length <= 16
s 仅由小写英文字母组成
 */
#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

class Solution {
    vector<vector<string>> ret;
    int size = 0;
    //记忆化，使用二维数组用来记录已经找出的回文串下标
    // -1:非回文串；0：需进一步判断；1：是回文串
    vector<vector<int>> is_palindrome;
    int is_recycle(string& s,int begin,int end){
        if(is_palindrome[begin][end])
            return is_palindrome[begin][end];
        if(begin >= end)
            return 1;
        return is_palindrome[begin][end] =  (s[begin] == s[end] ? (is_recycle(s,begin+1,end-1)) : -1);
    }

    void dfs(string& s,vector<string>& s_vc,int cur_idx){
        if(cur_idx >= size){
            ret.push_back(s_vc);
            return;
        }
        //找出所有以当前字符为开头的回文串
        for(int right = size -1;right >= cur_idx;right--){
            if(is_recycle(s,cur_idx,right) != 1)
                continue;
            //找到第一个回文串[cur_idx,right],放入数组
            s_vc.push_back(s.substr(cur_idx,right -cur_idx+1));
            //从right+1开始往后继续搜寻可能的回文串
            dfs(s,s_vc,right+1);
            //回溯，继续搜寻剩余的以当前节点为起始的回文串
            s_vc.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        size = static_cast<int>(s.size());
        vector<string> s_vc;
        is_palindrome.assign(size,vector<int>(size));
        dfs(s,s_vc,0);
        return ret;
    }
};

// int main(){
//     string s = "aab";
//     Solution sl;
//     const auto & vc = sl.partition(s);
//     for_each(vc.begin(),vc.end(),[](const vector<string>& v){
//         for_each(v.begin(),v.end(),[](const string& x){cout << x << " ";});
//         cout << endl;
//     });
//     return 0;
// }