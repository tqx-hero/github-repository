/**
  1160. 拼写单词
  简单
  相关标签
  premium lock icon
  相关企业
  提示
  给定一个字符串数组 words 和一个字符串 chars。

  如果字符串可以由 chars 中的字符组成（每个字符在 每个 words 中只能使用一次），则认为它是好的。

  返回 words 中所有好的字符串的长度之和。



  示例 1：

  输入：words = ["cat","bt","hat","tree"], chars = "atach"
  输出：6
  解释： 
  可以形成字符串 "cat" 和 "hat"，所以答案是 3 + 3 = 6。
  示例 2：

  输入：words = ["hello","world","leetcode"], chars = "welldonehoneyr"
  输出：10
  解释：
  可以形成字符串 "hello" 和 "world"，所以答案是 5 + 5 = 10。


  提示：

  1 <= words.length <= 1000
  1 <= words[i].length, chars.length <= 100
  words[i] 和 chars 中都仅包含小写英文字母
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countCharacters(char** words, int wordsSize, char* chars) {
    int cache[26],temp_cache[26] = {0};
    int ret,i,sz;
    char *word;
    while(*chars)
        temp_cache[*chars++ - 'a']++;
    ret = 0;
    for(i = 0;i < wordsSize;++i){
        memcpy(cache,temp_cache,sizeof(int) * 26);
        word = words[i];
        //遍历字符串
        for(sz = 0;word[sz]  && --cache[word[sz] - 'a'] >= 0;++sz);
        if(word[sz] == 0)
            ret += sz;
    }
    return ret;
}

int main(){
    char *words[] = {"cat","bt","hat","tree"}, *chars = "atach";
    fprintf(stdout,"%d\n",countCharacters(words,sizeof(words) / sizeof(char *) ,chars));
    exit(0);
}
