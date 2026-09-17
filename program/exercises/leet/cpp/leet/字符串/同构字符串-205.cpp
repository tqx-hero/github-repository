/**
 * 205. 同构字符串
简单
相关标签
premium lock icon
相关企业
给定两个字符串 s 和 t ，判断它们是否是同构的。

如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。

每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。

 

示例 1：

输入：s = "egg", t = "add"

输出：true

解释：

字符串 s 和 t 可以通过以下方式变得相同：

将 'e' 映射为 'a'。
将 'g' 映射为 'd'。
示例 2：

输入：s = "f11", t = "b23"

输出：false

解释：

字符串 s 和 t 无法变得相同，因为 '1' 需要同时映射到 '2' 和 '3'。

示例 3：

输入：s = "paper", t = "title"

输出：true

 

提示：

1 <= s.length <= 5 * 104
t.length == s.length
s 和 t 由任意有效的 ASCII 字符组成
 */
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<int,int> s_map,t_map;
        int size,i;
        if((size =s.size()) != t.size())
            return false;
        unordered_map<int,int>::iterator s_it,t_it;
        for(i=0;i<size;++i){
            s_it = s_map.find(s[i]);
            t_it = t_map.find(t[i]);
            bool s_target = s_it == s_map.end(),t_target = t_it == t_map.end();
            if(s_target && t_target){
                s_map[s[i]] = t[i];
                t_map[t[i]] = s[i];
            }
            else if(s_target || t_target || s_it->second != t[i])
                return false;
        }
        return true;
    }
};

// int main(){
//     // string s = "bbbaaaba", t = "aaabbbba";
//     // string s = "badc", t = "baba";
//     string s = "egg", t = "add";
//     Solution sl;
//     cout << sl.isIsomorphic(s,t) << endl;
//     return 0;
// }