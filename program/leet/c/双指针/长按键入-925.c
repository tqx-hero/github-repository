/**
925. 长按键入
简单
相关标签
premium lock icon
相关企业
你的朋友正在使用键盘输入他的名字 name。偶尔，在键入字符 c 时，按键可能会被长按，而字符可能被输入 1 次或多次。

你将会检查键盘输入的字符 typed。如果它对应的可能是你的朋友的名字（其中一些字符可能被长按），那么就返回 True。

 

示例 1：

输入：name = "alex", typed = "aaleex"
输出：true
解释：'alex' 中的 'a' 和 'e' 被长按。
示例 2：

输入：name = "saeed", typed = "ssaaedd"
输出：false
解释：'e' 一定需要被键入两次，但在 typed 的输出中不是这样。
 

提示：

1 <= name.length, typed.length <= 1000
name 和 typed 的字符都是小写字母
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//遍历name，查看每个字符会有连续几个出现，统计次数
//再遍历typed，查看这个字符是否出现次数不少于这个次数
bool isLongPressedName(char* name, char* typed) {
	int char_cnt = 1,ch,typed_cnt = 0; 
	while(1){
		//统计数量
		if(*name == *++name)
			char_cnt++;
		else{
			//不相等时，统计前面的这些字符
			ch = *(name - 1);
			while(*typed == ch){
				typed_cnt++;
				typed++;
			}
			//如果字符等于 0 ，统计结束
			if(char_cnt > typed_cnt || *name == 0)
				break;
			char_cnt = 1;
			typed_cnt = 0;
		}
	}
	return char_cnt <= typed_cnt && *typed == 0;
}

int main(){
//	char *name = "alex", *typed = "aaleex";
//	char *name = "alexd", *typed = "ale";
	char *name = "alex", *typed = "aaleexa";
	printf("%d \n",isLongPressedName(name,typed));
	return 0;
}
