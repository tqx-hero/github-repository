
/**
 *557. 反转字符串中的单词 III
简单
相关标签
premium lock icon
相关企业
给定一个字符串 s ，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。

 

示例 1：

输入：s = "Let's take LeetCode contest"
输出："s'teL ekat edoCteeL tsetnoc"
示例 2:

输入： s = "Mr Ding"
输出："rM gniD"
 

提示：

1 <= s.length <= 5 * 104
s 包含可打印的 ASCII 字符。
s 不包含任何开头或结尾空格。
s 里 至少 有一个词。
s 中的所有单词都用一个空格隔开。
 */
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
//就按照空格进行切分单词，逐个单词进行翻转
class Solution {
public:
    string reverseWords(string s) {
	size_t size = s.size();
	string ret,temp_str;
	int i;
	for(i = 0;i < size ;++i){
		//如果不是空格，放入临时数组
		if(s[i] != ' ')
			temp_str.push_back(s[i]);
		//是空格，就翻转temp中的字符，放入ret
		else{
			std::reverse(temp_str.begin(),temp_str.end());
			ret.append(temp_str);
			ret.push_back(' ');
			temp_str.clear();
		}
	}
	if(temp_str.size()){
		std::reverse(temp_str.begin(),temp_str.end());
		ret.append(temp_str);
	}
	return ret;
    }
};

int main(){
	string s = "Let's take LeetCode contest";
	Solution sl;
	cout << sl.reverseWords(s) << endl;
	return 0;
}
