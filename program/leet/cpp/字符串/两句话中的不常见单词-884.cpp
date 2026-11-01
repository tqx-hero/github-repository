/**
884. 两句话中的不常见单词
简单
相关标签
premium lock icon
相关企业
句子 是一串由空格分隔的单词。每个 单词 仅由小写字母组成。

如果某个单词在其中一个句子中恰好出现一次，在另一个句子中却 没有出现 ，那么这个单词就是 不常见的 。

给你两个 句子 s1 和 s2 ，返回所有 不常用单词 的列表。返回列表中单词可以按 任意顺序 组织。

 

示例 1：

输入：s1 = "this apple is sweet", s2 = "this apple is sour"
输出：["sweet","sour"]
示例 2：

输入：s1 = "apple apple", s2 = "banana"
输出：["banana"]
 

提示：

1 <= s1.length, s2.length <= 200
s1 和 s2 由小写英文字母和空格组成
s1 和 s2 都不含前导或尾随空格
s1 和 s2 中的所有单词间均由单个空格分隔
  */
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {

	void summary_words(unordered_map<string,int> &cache,const string &s){
		//按照空格字符截取单词
		int idx;
		size_t sz = s.size(),space_idx;
		string str;
		for(idx = 0;idx < sz;){
			//找到最近的空格
			space_idx = s.find(' ',idx);
			if(space_idx == std::string::npos)
				space_idx = sz;
			//截取字符串
			str = s.substr(idx,space_idx - idx);
			cache[str]++;
			idx = space_idx + 1;
		}
	}

public:
    vector<string> uncommonFromSentences(string s1, string s2) {
	    vector<string> ret;
	    unordered_map<string,int> cache;
	    summary_words(cache,s1);
	    summary_words(cache,s2);
	    for(auto& pair : cache){
		    if(pair.second == 1)
			    ret.push_back(pair.first);
	    }
	    return ret;
    }
};

int main(){
	string s1 = "this apple is sweet", s2 = "this apple is sour";
	Solution sl;
	const auto &vc = sl.uncommonFromSentences(s1,s2);
	for(int i =0;i<vc.size();++i)
		cout << vc[i] << endl;
	return 0;
}
