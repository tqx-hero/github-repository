
/**
953. 验证外星语词典
简单
相关标签
premium lock icon
相关企业
某种外星语也使用英文小写字母，但可能顺序 order 不同。字母表的顺序（order）是一些小写字母的排列。

给定一组用外星语书写的单词 words，以及其字母表的顺序 order，只有当给定的单词在这种外星语中按字典序排列时，返回 true；否则，返回 false。

 

示例 1：

输入：words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
输出：true
解释：在该语言的字母表中，'h' 位于 'l' 之前，所以单词序列是按字典序排列的。
示例 2：

输入：words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
输出：false
解释：在该语言的字母表中，'d' 位于 'l' 之后，那么 words[0] > words[1]，因此单词序列不是按字典序排列的。
示例 3：

输入：words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
输出：false
解释：当前三个字符 "app" 匹配时，第二个字符串相对短一些，然后根据词典编纂规则 "apple" > "app"，因为 'l' > '∅'，其中 '∅' 是空白字符，定义为比任何其他字符都小（更多信息）。
 

提示：

1 <= words.length <= 100
1 <= words[i].length <= 20
order.length == 26
在 words[i] 和 order 中的所有字符都是英文小写字母。
  */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
	bool compare_words(const string &little_str,const string &large_str,unordered_map<int,int> &cache){
		int i;
		size_t little_len = little_str.size(),large_len = large_str.size(),min_len = min(little_len,large_len);
		int sub;
		for(i = 0;i < min_len && (sub = cache[little_str[i]] -  cache[large_str[i]]) == 0 ;++i);
		if(i == min_len){
			if(little_len > large_len)
				return false;
			return true;
		}else
			return sub < 0;
	}
public:
    bool isAlienSorted(vector<string>& words, string order) {
	    int i;
	    size_t sz = order.size(),vsz = words.size();
	    if(vsz == 1)
		    return true;

	    unordered_map<int,int> cache;
	    //以字符为key，在字符串中的索引为value放入哈希表
	    for(i = 0;i < sz;++i)
		    cache[order[i] & 0xFF] = i;

	    //遍历数组，逐个比较字符
	    for(i = 1;i < vsz && compare_words(words[i - 1],words[i],cache);++i);
	    return i == vsz;
    }
};

int main(){
	vector<string> words{string{"hello"},string{"leetcode"}};
	string order = "hlabcdefgijkmnopqrstuvwxyz";
	Solution sl;
	cout << sl.isAlienSorted(words,order) << endl;
	return 0;
}
