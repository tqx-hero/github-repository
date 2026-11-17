/**
1304. 和为零的 N 个不同整数
简单
相关标签
premium lock icon
相关企业
提示
给你一个整数 n，请你返回 任意 一个由 n 个 各不相同 的整数组成的数组，并且这 n 个数相加和为 0 。

 

示例 1：

输入：n = 5
输出：[-7,-1,1,3,4]
解释：这些数组也是正确的 [-5,-1,1,2,3]，[-3,-1,2,-2,4]。
示例 2：

输入：n = 3
输出：[-1,0,1]
示例 3：

输入：n = 1
输出：[0]
 

提示：

1 <= n <= 1000
  */
#include <stdio.h>
#include <stdlib.h>

int* sumZero(int n, int* returnSize) {
    int *ret;
    int i,tempn,num;
    if((ret = malloc(sizeof(int) * n)) == NULL){
        perror("malloc()");
        exit(1);
    }
    *returnSize = n;
    if(n % 2)
        tempn = n - 1;
    else tempn = n;
    num = 1;
    //偶数个就从1开始遍历，同时放入i与-i
    for( i = 0 ; i < tempn ;++num)
    {
        ret[i++] = num;
        ret[i++] = -num;
    }
    if(tempn != n)
        ret[i] = 0;
    return ret;
}

int main(){
    int n = 5,returnSize;
    auto int *ret = sumZero(n,&returnSize);
    int i;
    for(i = 0;i < returnSize;++i)
        fprintf(stdout,"%d ",ret[i]);
    fprintf(stdout,"\n");
    free(ret);
    exit(0);
}
