/**
917. 仅仅反转字母
简单
相关标签
premium lock icon
相关企业
提示
给你一个字符串 s ，根据下述规则反转字符串：

所有非英文字母保留在原有位置。
所有英文字母（小写或大写）位置反转。
返回反转后的 s 。

 

示例 1：

输入：s = "ab-cd"
输出："dc-ba"
示例 2：

输入：s = "a-bC-dEf-ghIj"
输出："j-Ih-gfE-dCba"
示例 3：

输入：s = "Test1ng-Leet=code-Q!"
输出："Qedo1ct-eeLg=ntse-T!"
 

提示

1 <= s.length <= 100
s 仅由 ASCII 值在范围 [33, 122] 的字符组成
s 不含 '\"' 或 '\\'
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
char* reverseOnlyLetters(char* s) {
	int str_len,left,right,temp;
	str_len = strlen(s);
	for(left = 0, right = str_len - 1;left < right ;++left,--right){
		//找到左边的字母
		for(;left < right && !isalpha(s[left]);++left);
		for(;left < right && !isalpha(s[right]);--right);
		if(left < right){
			temp = s[left] & 0xff;
			s[left] = s[right] & 0xff;
			s[right] = temp;
		}
	}
	return s;
}

int main(){
	char s[] = "ab-cd";
	reverseOnlyLetters(s);
	printf("%s \n",s);
	return 0;
}
