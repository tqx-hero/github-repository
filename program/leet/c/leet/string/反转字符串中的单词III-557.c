#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//原地翻转，当遇到字符为空格时，反转前面的单词

void reverse_str(char* left,char* right){
	 while(left < right){
   		 char temp_ch = *left;
		 *left = *right;
		 *right =temp_ch;
		 ++left;
		 --right;
	 }
}

char* reverseWords(char* s) {
	char* sptr = s;
	char ch,*left =NULL,*right =NULL;
	while((ch = *sptr) != '\0'){
		if(ch == ' '){
			reverse_str(left,right);
			//恢复left、right指针
			left = NULL;
			right =NULL;
		}
		else if(!left){
			left = sptr;
			right =sptr;	
		}
		else 
			right =sptr;
		sptr++;
	}
	if(left && left < right)
		reverse_str(left,right);
	return s;
}

int main(){
	char s[] = "Let's take LeetCode contest";
	reverseWords(s);
	printf("%s\n",s);
	return 0;
}
