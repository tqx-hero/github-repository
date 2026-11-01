	
/**
859. 亲密字符串
简单
相关标签
premium lock icon
相关企业
给你两个字符串 s 和 goal ，只要我们可以通过交换 s 中的两个字母得到与 goal 相等的结果，就返回 true ；否则返回 false 。

交换字母的定义是：取两个下标 i 和 j （下标从 0 开始）且满足 i != j ，接着交换 s[i] 和 s[j] 处的字符。

例如，在 "abcd" 中交换下标 0 和下标 2 的元素可以生成 "cbad" 。
 

示例 1：

输入：s = "ab", goal = "ba"
输出：true
解释：你可以交换 s[0] = 'a' 和 s[1] = 'b' 生成 "ba"，此时 s 和 goal 相等。
示例 2：

输入：s = "ab", goal = "ab"
输出：false
解释：你只能交换 s[0] = 'a' 和 s[1] = 'b' 生成 "ba"，此时 s 和 goal 不相等。
示例 3：

输入：s = "aa", goal = "aa"
输出：true
解释：你可以交换 s[0] = 'a' 和 s[1] = 'a' 生成 "aa"，此时 s 和 goal 相等。
 

提示：

1 <= s.length, goal.length <= 2 * 104
s 和 goal 由小写英文字母组成
  */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool repeat(char *s){
    int hash_map[26] = {0};
    while(*s){
	if(++hash_map[*s - 'a'] > 1)
	    return true;
	s++;
    }
    return false;
}

bool buddyStrings(char* s, char* goal) {
    int len =  strlen(s);
    if(len != strlen(goal))
	return false;
    //如果两个字符串相同，需要查看字符串是否有重复字符
    if(!strncmp(s,goal,len))
	return repeat(s);
    //比较字符串，如果两个字符串有2处不同，并且这两处不同互相弥补，返回true，否则false
    int s1 = -1,s2 = -1,g1 = -1,g2 = -1,cnt = 0;
    while(*s && cnt <= 2){
	if(*s != *goal){
	    if(s1 == -1){
		s1 = *s;
		g1 = *goal;
	    }else{
		s2 = *s;
		g2 = *goal;
	    }
	    cnt++;
	}
	s++;
	goal++;
    }
    return cnt  == 2 && s1 == g2 && s2 == g1;
}

int main(){
    char *s = "ab", *goal = "ab";
   // setbuf(stdout,NULL);
    printf("value = %d\n",buddyStrings(s,goal));
    fflush(stdout);
//    printf("..................");
    return 0;
}
