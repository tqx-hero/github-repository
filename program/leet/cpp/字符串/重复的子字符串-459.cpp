#include <iostream>
#include <string>
using namespace std;

/**
 *459. 重复的子字符串
简单
相关标签
premium lock icon
相关企业
给定一个非空的字符串 s ，检查是否可以通过由它的一个子串重复多次构成。

 

示例 1:

输入: s = "abab"
输出: true
解释: 可由子串 "ab" 重复两次构成。
示例 2:

输入: s = "aba"
输出: false
示例 3:

输入: s = "abcabcabcabc"
输出: true
解释: 可由子串 "abc" 重复四次构成。 (或子串 "abcabc" 重复两次构成。)
 

提示：

1 <= s.length <= 104
s 由小写英文字母组成
 *
 */
//先统计词频，找到最小的那个字符个数。
//再遍历词频的数组，统计每个词频与最小个数的商，如果有除不尽的不满足要求
#include <unordered_map>
#include <algorithm>
//TODO 测试用例没走通，还需要再想办法
class Solution {
	//查找两个数的最大公约数
	int find_common(int n1,int n2){
		int min_val = min(n1,n2),max_val = max(n1,n2);
		while(true){
			if(max_val % min_val == 0)
				return min_val;
			int remain = max_val % min_val;
			max_val = min_val;
			min_val = remain;
		}
		return min_val;
	}

public:
    bool repeatedSubstringPattern(string s) {
	size_t size = s.size();
	unordered_map<int,int> hash_map;
	//统计词频
	for_each(s.begin(),s.end(),[&hash_map](const char &ch){hash_map[ch]++;});
	//遍历词频数组，找到这些词频的最大公约数
	int min_cnt = 0;
	for(auto& entry: hash_map){
		if(min_cnt == 0)
			min_cnt = entry.second;
		else
			min_cnt = find_common(entry.second,min_cnt);
	}
	//如果最少是1个，不满足要求
	if(min_cnt == 1)
		return false;
	//子串长度
	int substr_len =0;
	for(auto& entry : hash_map)
		//把商添加到子串长度
		substr_len += entry.second / min_cnt;
	int i,j;
	for(i=substr_len;i < size;){
		//比较0~substr_len-1与substr_len~2*substr_len-1的字符串，看是否完全匹配
		for(j=0;j < substr_len && s[j] == s[i];++j,++i);
		if(j < substr_len)
			return false;
	}
	return true;
    }
};

int main(){
//	string s = "abab";
	//string s = "aba";
//	string s = "abcabcabcabc";
//	string s = "abaababaab";
	string s = "babbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbb";
	Solution sl;
	cout << sl.repeatedSubstringPattern(s) << endl;
	return 0;
}
