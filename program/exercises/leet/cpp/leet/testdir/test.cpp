/**
 * 290. 单词规律
简单
相关标签
premium lock icon
相关企业
给定一种规律 pattern 和一个字符串 s ，判断 s 是否遵循相同的规律。

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 s 中的每个非空单词之间存在着双向连接的对应规律。具体来说：

pattern 中的每个字母都 恰好 映射到 s 中的一个唯一单词。
s 中的每个唯一单词都 恰好 映射到 pattern 中的一个字母。
没有两个字母映射到同一个单词，也没有两个单词映射到同一个字母。
 

示例1:

输入: pattern = "abba", s = "dog cat cat dog"
输出: true
示例 2:

输入:pattern = "abba", s = "dog cat cat fish"
输出: false
示例 3:

输入: pattern = "aaaa", s = "dog cat cat dog"
输出: false
 

提示:

1 <= pattern.length <= 300
pattern 只包含小写英文字母
1 <= s.length <= 3000
s 只包含小写英文字母和 ' '
s 不包含 任何前导或尾随对空格
s 中每个单词都被 单个空格 分隔
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution {
    void build_array(string& s,vector<string>& vct){
        //按照空格拆分字符串
        int size = static_cast<int>(s.size()),i;
        string str;
        for(i=0;i<size;++i){
            if(s[i] == ' '){
                vct.push_back(str);
                str.clear();
            }else
                str.push_back(s[i]);
        }
        vct.push_back(str);
    }
public:
    bool wordPattern(string pattern, string s) {
        vector<string> vct;
        build_array(s,vct);
        int i,size;
        if((size = pattern.size()) != vct.size())
            return false;
        unordered_map<char,string> c_map;
        unordered_map<string,char> s_map;
        unordered_map<char,string>::iterator c_it;
        unordered_map<string,char>::iterator s_it;
        for(i=0;i<size;++i){
            c_it = c_map.find(pattern[i]);
            s_it = s_map.find(vct[i]);
            bool c_no = c_it == c_map.end(),s_no = s_it == s_map.end();
            //如果都不存在，进行插入
            if(c_no && s_no){
                c_map[pattern[i]] = vct[i];
                s_map[vct[i]] = pattern[i];
            }else if(c_no || s_no || s_it->second != pattern[i])
                return false;
        }
        return true;
    }
};

// int main(){
//     // string pattern = "abba", s = "dog cat cat dog";
//     // string pattern = "abba", s = "dog cat cat fish";
//     string pattern = "aaaa", s = "dog cat cat dog";
//     Solution sl;
//     cout << sl.wordPattern(pattern,s) << endl;
//     return 0;
// }