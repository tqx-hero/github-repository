/**
1317. 将整数转换为两个无零整数的和
简单
相关标签
premium lock icon
相关企业
提示
「无零整数」是十进制表示中 不含任何 0 的正整数。

给你一个整数 n，请你返回一个 由两个整数组成的列表 [a, b]，满足：

a 和 b 都是无零整数
a + b = n
题目数据保证至少有一个有效的解决方案。

如果存在多个有效解决方案，你可以返回其中任意一个。

 

示例 1：

输入：n = 2
输出：[1,1]
解释：a = 1, b = 1。a + b = n 并且 a 和 b 的十进制表示形式都不包含任何 0。
示例 2：

输入：n = 11
输出：[2,9]
示例 3：

输入：n = 10000
输出：[1,9999]
示例 4：

输入：n = 69
输出：[1,68]
示例 5：

输入：n = 1010
输出：[11,999]
 

提示：

2 <= n <= 104
  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
static int contain0(int x){
    int i = 0;
    while(x){
        if(x % 10  == 0)
            return i;
        i++;
        x /= 10;
    }
    return -1;
}

int* getNoZeroIntegers(int n, int* returnSize) {
    int *ret;
    int n1,n2;
    int x1,x2,remain;
    if((ret = malloc(sizeof(int) * 2)) == NULL)
    {
        perror("malloc()");
        exit(1);
    }
    n1 = 1,n2 = n - n1;
    while((x1 = contain0(n1)) >= 0 || (x2 = contain0(n2)) >= 0)
    {
        if(x1 >= 0)
        {
            remain = pow(10,x1);
            n1 -= remain;
            n2 += remain;
        }else
        {
            remain = pow(10,x2);
            n1 += remain;
            n2 -= remain;
        }
    }
    ret[0] = n1;
    ret[1] = n2;
    *returnSize = 2;
    return ret;
}

int main(){
    int n = 1010,returnSize;
    int *ret = getNoZeroIntegers(n,&returnSize);
    fprintf(stdout,"%d %d \n",ret[0],ret[1]);
    free(ret);
    exit(0);
}
