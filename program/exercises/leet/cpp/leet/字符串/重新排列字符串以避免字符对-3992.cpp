/**
 * 3992. 重新排列字符串以避免字符对
简单
相关标签
premium lock icon
相关企业
提示
给你一个字符串 s 和两个 不同 的小写英文字母 x 和 y。

重新排列 s 中的字符来构造一个新的字符串 t，使得：

t 是 s 的一个 排列。
在 t 中，所有 y 都必须在所有 x 之前。
返回 任意 一个有效的字符串 t。

排列 是对一个字符串中所有字符的重新排列。

 

示例 1：

输入： s = "aabc", x = "a", y = "c"

输出： "cbaa"

解释：

字符串 "cbaa" 是 "aabc" 的一个排列，且每次出现的 'c' 都在每次出现的 'a' 之前。

示例 2：

输入： s = "dcab", x = "d", y = "b"

输出： "cabd"

解释：

字符串 "cabd" 是 "dcab" 的一个排列，且每次出现的 'b' 都在每次出现的 'd' 之前。

示例 3：

输入： s = "axe", x = "o", y = "x"

输出： "axe"

解释：

字符串 "axe" 已经有效。因为 'o' 没有在字符串中出现，所以自动满足要求的条件。

 

提示：

1 <= s.length <= 100
s 仅由小写英文字母组成。
x 和 y 都是小写英文字母。
x != y
 */
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    string rearrangeString(string s, char x, char y) {
        //双指针按照快排方式交换x、y位置，使得y在x前面
        int size =static_cast<int>(s.size()),left,right;
        for(left =0,right =size -1;left < right;++left,--right){
            //左指针从左往右查找x
            //右指针从右往左查找y
            for(;left < right && s[left] != x ; ++left);
            for(;left < right && s[right] != y ;--right);
            if(left < right)
                swap(s[left],s[right]);
        }
        return s;
    }
};

// int main(){
//     string s = "aabc", x = "a", y = "c";
//     Solution sl;
//     cout << sl.rearrangeString(s,x,y) << endl;
//     return 0;
// }