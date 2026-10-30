/**
748. 最短补全词
简单
相关标签
premium lock icon
相关企业
提示
给你一个字符串 licensePlate 和一个字符串数组 words ，请你找出 words 中的 最短补全词 。

补全词 是一个包含 licensePlate 中所有字母的单词。忽略 licensePlate 中的 数字和空格 。不区分大小写。如果某个字母在 licensePlate 中出现不止一次，那么该字母在补全词中的出现次数应当一致或者更多。

例如：licensePlate = "aBc 12c"，那么它的补全词应当包含字母 'a'、'b' （忽略大写）和两个 'c' 。可能的 补全词 有 "abccdef"、"caaacab" 以及 "cbca" 。

请返回 words 中的 最短补全词 。题目数据保证一定存在一个最短补全词。当有多个单词都符合最短补全词的匹配条件时取 words 中 第一个 出现的那个。

 

示例 1：

输入：licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
输出："steps"
解释：最短补全词应该包括 "s"、"p"、"s"（忽略大小写） 以及 "t"。
"step" 包含 "t"、"p"，但只包含一个 "s"，所以它不符合条件。
"steps" 包含 "t"、"p" 和两个 "s"。
"stripe" 缺一个 "s"。
"stepple" 缺一个 "s"。
因此，"steps" 是唯一一个包含所有字母的单词，也是本例的答案。
示例 2：

输入：licensePlate = "1s3 456", words = ["looks", "pest", "stew", "show"]
输出："pest"
解释：licensePlate 只包含字母 "s" 。所有的单词都包含字母 "s" ，其中 "pest"、"stew"、和 "show" 三者最短。答案是 "pest" ，因为它是三个单词中在 words 里最靠前的那个。
 

提示：

1 <= licensePlate.length <= 7
licensePlate 由数字、大小写字母或空格 ' ' 组成
1 <= words.length <= 1000
1 <= words[i].length <= 15
words[i] 由小写英文字母组成
  */
#include <vector>
#include <string>
#include <iostream>
#include <locale>
#include <climits>
#include <unordered_map>
using namespace std;
class Solution {

    bool contains_str(string& str,unordered_map<char,int> cache,int char_cnt){
	unordered_map<char,int>::iterator it;
	for(auto& ch : str){
	   if((it =  cache.find(ch)) == cache.end())
	       continue;
	   if(--it->second == 0)
	       cache.erase(ch);
	   char_cnt--;
	}
	return char_cnt == 0;
    }

public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
	unordered_map<char,int> cache;
	std::locale loc;
	char chr;
	int char_cnt =0;
	for(auto& ch: licensePlate){
	    if(std::islower((chr = ch | 0x20),loc)){
		cache[chr]++;
		char_cnt++;
	    }
	}
	size_t sz = words.size();
	int i;
	int ret_size = INT_MAX,ret_idx,cur_size;
	for(i=0;i < sz;++i){
	    if(contains_str(words[i],cache,char_cnt) && (cur_size = words[i].size()) < ret_size){
		ret_idx = i;
		ret_size = cur_size;
	    }
	}
	return words[ret_idx];
    }
};

int main(){
    //licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
    string licensePlate = "1s3 PSt";
    vector<string> words{
	string{"step"},
	string{"steps"},
	string{"stripe"},
	string{"stepple"}
    };
    Solution sl;
    cout << sl.shortestCompletingWord(licensePlate,words) << endl;
    return 0;
}
