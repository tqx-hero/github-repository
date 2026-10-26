/**
 *541. 反转字符串 II
简单
相关标签
premium lock icon
相关企业
给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k 字符中的前 k 个字符，再重新计数。

如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
 

示例 1：

输入：s = "abcdefg", k = 2
输出："bacdfeg"
示例 2：

输入：s = "abcd", k = 2
输出："bacd"
 

提示：

1 <= s.length <= 104
s 仅由小写英文组成
1 <= k <= 104
 */
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    string reverseStr(string s, int k) {
	    size_t size = s.size();
	    if(k >= size)
		    std::reverse(s.begin(),s.end());
	    else{
		    //按照k个字符反转
		    int i;
		    //更新i跳过k个字节
		    for(i=0;i<size;i += 2*k){
			    if(i+k <= size)
				    std::reverse(s.begin()+i,s.begin()+i+k);
			    else
				    std::reverse(s.begin()+i,s.end());
		    }
	    }
	    return s;
    }
};

int main(){
	//string s = "abcdefg";
	string s = "abcd";
	int k = 2;
	Solution sl;
	cout << sl.reverseStr(s,k) << endl;
	return 0;
}
