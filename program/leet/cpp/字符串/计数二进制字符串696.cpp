/**
 *696. 计数二进制子串
简单
相关标签
premium lock icon
相关企业
提示
给定一个字符串 s，统计并返回具有相同数量 0 和 1 的非空（连续）子字符串的数量，并且这些子字符串中的所有 0 和所有 1 都是成组连续的。

重复出现（不同位置）的子串也要统计它们出现的次数。

 
示例 1：

输入：s = "00110011"
输出：6
解释：6 个子串满足具有相同数量的连续 1 和 0 ："0011"、"01"、"1100"、"10"、"0011" 和 "01" 。
注意，一些重复出现的子串（不同位置）要统计它们出现的次数。
另外，"00110011" 不是有效的子串，因为所有的 0（还有 1 ）没有组合在一起。
示例 2：

输入：s = "10101"
输出：4
解释：有 4 个子串："10"、"01"、"10"、"01" ，具有相同数量的连续 1 和 0 。
 

提示：

1 <= s.length <= 105
s[i] 为 '0' 或 '1'
 */
#include <string>
#include <iostream>
#include <array>
using namespace std;

class Solution {
public:
    int countBinarySubstrings(string s) {
	    array<int,2> cache{0};
	    cache[s[0]-'0']++;
	    size_t size = s.size();
	    int cnt =0,i;
	    for(i=1;i < size;i++){
		    char ch = s[i];
		    if(ch == s[i-1])//如果当前字符与上个字符相同，直接增加1
			    cache[ch -'0']++;
		    else	//不等于时，将他所在的下标值清空并+1
			    cache[ch - '0'] = 1;
		    //如果当前数组个数不大于另一个坑的个数，计数+1
		    if(cache[ch - '0'] <= cache[(ch- '0' + 1) % 2])
			    cnt++;
	    }
	    return cnt;
    }
};

int main(){
//	string s = "00110011";
	string s = "10101";
	Solution sl;
	cout << sl.countBinarySubstrings(s) << endl;
	return 0;
}
