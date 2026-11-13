/**
  1078. Bigram 分词
  简单
  相关标签
  premium lock icon
  相关企业
  提示
  给出第一个词 first 和第二个词 second，考虑在某些文本 text 中可能以 "first second third" 形式出现的情况，其中 second 紧随 first 出现，third 紧随 second 出现。

  对于每种这样的情况，将第三个词 "third" 添加到答案中，并返回答案。



  示例 1：

  输入：text = "alice is a good girl she is a good student", first = "a", second = "good"
  输出：["girl","student"]
  示例 2：

  输入：text = "we will we will rock you", first = "we", second = "will"
  输出：["we","rock"]


  提示：

  1 <= text.length <= 1000
  text 由小写英文字母和空格组成
  text 中的所有单词之间都由 单个空格字符 分隔
  1 <= first.length, second.length <= 10
  first 和 second 由小写英文字母组成
  text 不包含任何前缀或尾随空格。
 */
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>

char** findOcurrences(char* text, char* first, char* second, int* returnSize) {
    char *saveptr,*token,*temp_saveptr;
    int i = 0;
    glob_t globres;
    for(;token = strtok_r(text," ",&saveptr);){
        //如果第一个字符串相同，指针前移，找到第二个字符串
        if(strcmp(first,token) == 0){
            temp_saveptr = saveptr;
            token = strtok_r(NULL," ",&saveptr);
            if(!token)
                break;
            //相同就把下一个放入数组
            if(strcmp(token,second) == 0){
                saveptr[-1] = ' ';
                token = strtok_r(NULL," ",&saveptr);
                if(!token)
                    break;
                glob(token,GLOB_NOCHECK | GLOB_APPEND * i,NULL,&globres);
                saveptr[-1] = ' ';
                i = 1;
            }else
                saveptr[-1] = ' ';
            //指针回退
            text = temp_saveptr;
        }
        else text = NULL;
    }
    *returnSize = globres.gl_pathc;
    return globres.gl_pathv;
}


int main(){
    char text[] = "alice is a good girl she is a good student", *first = "a", *second = "good";
    int returnSize;
    char **ret = findOcurrences(text,first,second,&returnSize);
    char *temp;
    fprintf(stdout,"returnSize = %d\n",returnSize);
    while(*ret){
        fprintf(stdout,"%s\n",*ret);
        temp = *ret;
        ret++;
    }
    return 0;
}
