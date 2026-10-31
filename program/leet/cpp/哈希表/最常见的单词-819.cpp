/**
819. 最常见的单词
简单
相关标签
premium lock icon
相关企业
给你一个字符串 paragraph 和一个表示禁用词的字符串数组 banned ，返回出现频率最高的非禁用词。题目数据 保证 至少存在一个非禁用词，且答案 唯一 。

paragraph 中的单词 不区分大小写 ，答案应以 小写 形式返回。

注意 单词不包含标点符号。

 

示例 1：

输入：paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.", banned = ["hit"]
输出："ball"
解释：
"hit" 出现了 3 次，但它是禁用词。
"ball" 出现了两次（没有其他单词出现这么多次），因此它是段落中出现频率最高的非禁用词。
请注意，段落中的单词不区分大小写，
标点符号会被忽略（即使它们紧挨着单词，如 "ball,"），
并且尽管 "hit" 出现的次数更多，但它不能作为答案，因为它是禁用词。
示例 2：

输入：paragraph = "a.", banned = []
输出："a"
 

提示：

1 <= paragraph.length <= 1000
paragraph 由英文字母、空格 ' '、和以下符号组成："!?',;."
0 <= banned.length <= 100
1 <= banned[i].length <= 10
banned[i] 仅由小写英文字母组成
  */
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <locale>
#include <iostream>
using namespace std;

class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
	paragraph.push_back('.');
	unordered_set<string> cache{banned.begin(),banned.end()};
	unordered_map<string,int> hash_map;
	size_t sz = paragraph.size();
	int i;
	int cnt = 0,cur_cnt;
	std:: locale loc;
	string str,ret_str;
	for(i = 0;i < sz;++i){
	    char ch = paragraph[i];
	    if(std::isalpha(ch,loc)){//如果字符为字母，放入str
		str.push_back(std::tolower(ch,loc));
	    }else{//不为字符，判断str是否为空，不为空则统计字符串
		if(str.empty())
		    continue;
		//如果不存在禁忌词中，放入哈希表，并统计次数
		if(!cache.count(str) && (cur_cnt = ++hash_map[str]) > cnt){
		    ret_str = str;
		    cnt = cur_cnt;
		}
		str.clear();
	    }
	}
	return ret_str;
    }
};

int main(){
    string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
	   vector<string> banned{string{"hit"}};
    Solution sl;
    cout << sl.mostCommonWord(paragraph,banned) << endl;
	return 0;
}
