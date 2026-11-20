/**
  1380. 矩阵中的幸运数
  简单
  相关标签
  premium lock icon
  相关企业
  提示
  给你一个 m x n 的矩阵，矩阵中的数字 各不相同 。请你按 任意 顺序返回矩阵中的所有幸运数。

  幸运数 是指矩阵中满足同时下列两个条件的元素：

  在同一行的所有元素中最小
  在同一列的所有元素中最大


  示例 1：

  输入：matrix = [[3,7,8],[9,11,13],[15,16,17]]
  输出：[15]
  解释：15 是唯一的幸运数，因为它是其所在行中的最小值，也是所在列中的最大值。
  示例 2：

  输入：matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
  输出：[12]
  解释：12 是唯一的幸运数，因为它是其所在行中的最小值，也是所在列中的最大值。
  示例 3：

  输入：matrix = [[7,8],[1,2]]
  输出：[7]
  解释：7 是唯一的幸运数字，因为它是行中的最小值，列中的最大值。


  提示：

  m == mat.length
  n == mat[i].length
  1 <= n, m <= 50
  1 <= matrix[i][j] <= 105
  矩阵中的所有元素都是不同的
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static inline int min(const int x,const int y)
{
    return x <= y ? x : y;
}

int* luckyNumbers(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int *ret,*cache,*pattern;
    int cnt = 0,i,j,minval,minidx;
    cache = malloc(sizeof(int) * matrixSize);
    pattern = calloc(matrixSize,sizeof(int));

    for(i = 0;i < matrixSize;++i)
    {
        minval = INT_MAX;
        for(j = 0;j < matrixColSize[i];++j)
        {
            if(matrix[i][j] < minval)
            {
                minval = matrix[i][j];
                minidx = j;
            }
        }
        cache[i] = minidx;
    }

    //进行按列比较,统计满足条件的个数
    for(i = 0;i < matrixSize;++i)
    {
        minidx = cache[i];
        minval = matrix[i][minidx];
        for(j = 0;j < matrixSize && matrix[j][minidx] <= minval;++j);
        if(j == matrixSize)
        {
            cnt++;
            pattern[i] = 1;
        }
    }

    ret = malloc(sizeof(int) * cnt);
    j = 0;
    for(i = 0;i < matrixSize;++i)
        if(pattern[i])
            ret[j++] = matrix[i][cache[i]];

    *returnSize = cnt;
    free(cache);
    free(pattern);
    return ret;
}

int main(){
    int* matrix[] = {(int[]){1, 10, 4, 2}, (int[]){9, 3, 8, 7}, (int[]){15, 16, 17, 12}};
    int matrixSize = 3;
    int matrixColSize[] = {4, 4, 4};
    int returnSize;
    int *ret = luckyNumbers(matrix,matrixSize,matrixColSize,&returnSize);
    int i;
    for(i = 0; i< returnSize;++i)
        fprintf(stdout,"%d ",ret[i]);
    fprintf(stdout,"\n");
    free(ret);
    exit(0);
}
