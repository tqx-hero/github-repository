/**
806. 写字符串需要的行数
已解答
简单
相关标签
premium lock icon
相关企业
我们要把给定的字符串 S 从左到右写到每一行上，每一行的最大宽度为100个单位，如果我们在写某个字母的时候会使这行超过了100 个单位，那么我们应该把这个字母写到下一行。我们给定了一个数组 widths ，这个数组 widths[0] 代表 'a' 需要的单位， widths[1] 代表 'b' 需要的单位，...， widths[25] 代表 'z' 需要的单位。

现在回答两个问题：至少多少行能放下S，以及最后一行使用的宽度是多少个单位？将你的答案作为长度为2的整数列表返回。

示例 1:
输入: 
widths = [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
S = "abcdefghijklmnopqrstuvwxyz"
输出: [3, 60]
解释: 
所有的字符拥有相同的占用单位10。所以书写所有的26个字母，
我们需要2个整行和占用60个单位的一行。
示例 2:
输入: 
widths = [4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
S = "bbbcccdddaaa"
输出: [2, 4]
解释: 
除去字母'a'所有的字符都是相同的单位10，并且字符串 "bbbcccdddaa" 将会覆盖 9 * 10 + 2 * 4 = 98 个单位.
最后一个字母 'a' 将会被写到第二行，因为第一行只剩下2个单位了。
所以，这个答案是2行，第二行有4个单位宽度。
 

注:

字符串 S 的长度在 [1, 1000] 的范围。
S 只包含小写字母。
widths 是长度为 26的数组。
widths[i] 值的范围在 [2, 10]。
  */
#include <stdio.h>
#include <stdlib.h>

int* numberOfLines(int* widths, int widthsSize, char* s, int* returnSize) {
    int *ret = (int*) malloc(sizeof(int) * 2);
    if(!ret){
	perror("malloc error");
	exit(EXIT_FAILURE);
    }
    *returnSize = 2;
    int max = 100,line = 1,cur_num = 0;
    while(*s){
	int temp = widths[*s - 'a'] + cur_num;
	if(temp > max){//相加后大于当前的最大长度限制，需要line+1
	    line++;
	    cur_num = widths[*s - 'a'];
	}else if(temp == max){
	    line++;
	    cur_num = 0;
	}else
	    cur_num = temp;
	s++;
    }
    if(cur_num){
	ret[0] = line;
	ret[1] = cur_num;
    }else{
	ret[0] = line -1;
	ret[1] = max;
    }
    return ret;
}

int main(){
    int widths[] = {4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
    char* S = "bbbcccdddaaa";
    int returnSize;
    int *ret = numberOfLines(widths,26,S,&returnSize);
    printf("行数 = %d\n",ret[0]);
    printf("长度 = %d\n",ret[1]);
    free(ret);
    return 0;
}
