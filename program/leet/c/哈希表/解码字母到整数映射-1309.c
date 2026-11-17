/**
1309. 解码字母到整数映射
简单
相关标签
premium lock icon
相关企业
提示
给你一个字符串 s，它由数字（'0' - '9'）和 '#' 组成。我们希望按下述规则将 s 映射为一些小写英文字符：

字符（'a' - 'i'）分别用（'1' - '9'）表示。
字符（'j' - 'z'）分别用（'10#' - '26#'）表示。 
返回映射之后形成的新字符串。

题目数据保证映射始终唯一。

 

示例 1：

输入：s = "10#11#12"
输出："jkab"
解释："j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".
示例 2：

输入：s = "1326#"
输出："acz"
 

提示：

1 <= s.length <= 1000
s[i] 只包含数字（'0'-'9'）和 '#' 字符。
s 是映射始终存在的有效字符串。
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* freqAlphabets(char* s) {
    size_t size = strlen(s);
    char *ret;
    int i,j;
    if((ret = malloc(size + 1)) == NULL)
    {
        perror("malloc()");
        exit(1);
    }
    j = 0;
    for(i = 0; i < size ; ++j)
    {
        if(i + 2 < size && s[i + 2] == '#')//如果是带#的
        {
            ret[j] = atoi(s + i) - 1 + 'a';
            i += 3;
        }else
        {
            ret[j] = s[i] - '1' + 'a'; 
            i++;
        }
    }
    ret[j] = 0;
    return ret;
}

int main(){
    char *s = "10#11#12";
    char *ret = freqAlphabets(s);
    fprintf(stdout,"%s\n",ret);
    free(ret);
    exit(0);
}
