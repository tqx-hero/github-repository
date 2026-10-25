/**
 *520. 检测大写字母
简单
相关标签
premium lock icon
相关企业
我们定义，在以下情况时，单词的大写用法是正确的：

全部字母都是大写，比如 "USA" 。
所有字母都不是大写，比如 "leetcode" 。
只有首字母大写， 比如 "Google" 。
给你一个字符串 word 。如果大写用法正确，返回 true ；否则，返回 false 。

 

示例 1：

输入：word = "USA"
输出：true
示例 2：

输入：word = "FlaG"
输出：false
 

提示：

1 <= word.length <= 100
word 由小写和大写英文字母组成
 */
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    bool detectCapitalUse(string word) {
	    size_t size = word.size();
	    if(size ==1)
		    return true;
	    bool allow_upper = (word[0] < 97),allow_lower = true;
	    int i;
	    for(i=1;i<size;++i){
		    //如果字符是大写，并且不允许大写，返回false
		    if(word[i] < 97){
			    if(!allow_upper)
				    return false;
			//允许大写，那后面必然不允许小写
			allow_lower = false;
		    }else{
		    	//查看是否允许小写字母，不允许直接返回false
			if(!allow_lower)
				return false;
			//允许小写就不能允许大写
			allow_upper = false;
		    }
	    }
	    return true;
    }
};

int main(){
	string word = "FlaG";
	Solution sl;
	cout << sl.detectCapitalUse(word) << endl;
	return 0;
}
