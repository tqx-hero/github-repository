/**
1002. 查找共用字符
简单
相关标签
premium lock icon
相关企业
给你一个字符串数组 words ，请你找出所有在 words 的每个字符串中都出现的共用字符（包括重复字符），并以数组形式返回。你可以按 任意顺序 返回答案。
 

示例 1：

输入：words = ["bella","label","roller"]
输出：["e","l","l"]
示例 2：

输入：words = ["cool","lock","cook"]
输出：["c","o"]
 

提示：

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] 由小写英文字母组成
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
void* Malloc(size_t size){
	void *ret;
	if(!(ret = malloc(size))){
		perror("malloc error()");
		exit(1);
	}
	return ret;
}

void update_hashmap(const char *str,int *hash_map){
	while(*str)
		hash_map[*str++ - 'a']++;
}

char** commonChars(char** words, int wordsSize, int* returnSize) {
	char * str,*evstr;
	char ** ret;
	int hash_map[26] = {0};
	int cnt,i,j,k;
	ret = (char**)Malloc(MAX_SIZE * sizeof(char*));
	//使用第一个字符串初始化hash_map
	update_hashmap(*words,hash_map);
	//从第二个开始与哈希表进行比对
	k = 1;
	while(k < wordsSize){
		str = words[k];
		int temp_hash[26] = {0};
		while(*str){//统计当前字符串与哈希表对应的字符与个数，放入临时哈希表
			if(--hash_map[*str - 'a'] >= 0)
				temp_hash[*str - 'a']++;
			str++;
		}
		//把临时哈希表同步到hash_map
		memcpy(hash_map,temp_hash,sizeof(temp_hash));
		k++;
	}
	for(cnt = 0,i = 0;i < 26;++i){
		j = hash_map[i];
		while(j--){
			evstr = Malloc(2);
			evstr[0] = (i & 0xFF) + 'a';
			evstr[1] = 0;
			ret[cnt++] = evstr;
		}
	}
	*returnSize = cnt;
	return ret;
}

int main(){
	char *words[] = {"bella","label","roller"};
	int returnSize;
	char ** ret = commonChars(words,sizeof(words) / sizeof(char*),&returnSize);
	for(int i = 0;i < returnSize;++i){
		fprintf(stdout,"%s ",ret[i]);
		free(ret[i]);
	}
	fprintf(stdout,"\n");
	free(ret);
	return 0;
}
