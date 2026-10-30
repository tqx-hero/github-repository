/**
830. 较大分组的位置
简单
相关标签
premium lock icon
相关企业
在一个由小写字母构成的字符串 s 中，包含由一些连续的相同字符所构成的分组。

例如，在字符串 s = "abbxxxxzyy" 中，就含有 "a", "bb", "xxxx", "z" 和 "yy" 这样的一些分组。

分组可以用区间 [start, end] 表示，其中 start 和 end 分别表示该分组的起始和终止位置的下标。上例中的 "xxxx" 分组用区间表示为 [3,6] 。

我们称所有包含大于或等于三个连续字符的分组为 较大分组 。

找到每一个 较大分组 的区间，按起始位置下标递增顺序排序后，返回结果。

 

示例 1：

输入：s = "abbxxxxzzy"
输出：[[3,6]]
解释："xxxx" 是一个起始于 3 且终止于 6 的较大分组。
示例 2：

输入：s = "abc"
输出：[]
解释："a","b" 和 "c" 均不是符合要求的较大分组。
示例 3：

输入：s = "abcdddeeeeaabbbcd"
输出：[[3,5],[6,9],[12,14]]
解释：较大分组为 "ddd", "eeee" 和 "bbb"
示例 4：

输入：s = "aba"
输出：[]
 
提示：

1 <= s.length <= 1000
s 仅含小写英文字母
  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int** largeGroupPositions(char* s, int* returnSize, int** returnColumnSizes) {
    int str_len = strlen(s),arr_len = str_len / 3;
    *returnColumnSizes = (int*) malloc(sizeof(int) * arr_len);
    int** ret = (int**) malloc(sizeof(int*) * arr_len);
    int i;
    int ret_size = 0,cnt = 1;
    for(i=1; i <= str_len ;++i){
	if(s[i] == s[i-1])
	    cnt++;
	else{ //如果不相同，那就统计前面的值是否超过三个
	    if(cnt >= 3){//如果长度超过3，统计这个区间
		int *val = (int*) malloc(sizeof(int) * 2);
		(*returnColumnSizes)[ret_size] = 2;
		val[0] = i - cnt;
		val[1] = i - 1;
		ret[ret_size++] = val;
	    }
	    cnt = 1;
	}
    }
    *returnSize = ret_size;
    return ret;
}

int main(){
//    char *s =  "abbxxxxzzy";
//    char * s = "abc";
    char * s = "abcdddeeeeaabbbcd";
    int returnSize;
    int *returnColumnSizes,**ret;
    ret = largeGroupPositions(s,&returnSize,&returnColumnSizes);
    int i,j;
    for(i=0;i < returnSize;++i){
	int * vc = ret[i];
	for(j=0;j < returnColumnSizes[i] ;++j)
	    printf("%d = %d\n",j + 1,vc[j]);
	printf("-------------------\n");
	free(vc);
    }
    free(returnColumnSizes);
    free(ret);
    return 0;
}
