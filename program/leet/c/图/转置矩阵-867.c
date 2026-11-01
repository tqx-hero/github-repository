/**
867. 转置矩阵
简单
相关标签
premium lock icon
相关企业
提示
给你一个二维整数数组 matrix， 返回 matrix 的 转置矩阵 。

矩阵的 转置 是指将矩阵的主对角线翻转，交换矩阵的行索引与列索引。



 

示例 1：

输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[1,4,7],[2,5,8],[3,6,9]]
示例 2：

输入：matrix = [[1,2,3],[4,5,6]]
输出：[[1,4],[2,5],[3,6]]
 

提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 1000
1 <= m * n <= 105
-109 <= matrix[i][j] <= 109
  */
#include <stdlib.h>
#include <stdio.h>

void* Malloc(size_t size){
    void* ret;
    if(!(ret = malloc(size))){
	perror("malloc error");
	exit(EXIT_FAILURE);
    }
    return ret;
}

int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {
    int** ret,row,col;
    int i,j;
    //申请内存空间
    row = *matrixColSize;
    col = matrixSize;
    ret = (int**)Malloc(sizeof(int*) * row);
    *returnSize = row;
    *returnColumnSizes = (int*) Malloc(sizeof(int) * row);
    //填充列数
    //申请每一行空间
    for(i=0;i < row;++i){
	    ret[i] = (int*) Malloc(sizeof(int) * col);
	    (*returnColumnSizes)[i] = col;
    }
    //遍历原二维数组
    for(i=0;i < col;++i)
	for(j =0;j < row;++j)
	    ret[j][i] = matrix[i][j];
    return ret;
}

int main(){
    //matrix = [[1,2,3],[4,5,6],[7,8,9]]
//	int v1[]={1,2,3},v2[] = {4,5,6},v3[] = {7,8,9};
//	int *arr[] = {v1,v2,v3};
	//matrix = [[1,2,3],[4,5,6]]
	int v1[]={1,2,3},v2[] = {4,5,6};
	int *arr[] = {v1,v2};
	int matrixColSize = sizeof(v1) / sizeof(int);
	int returnSize,*returnColumnSizes;
	int **ret = transpose(arr,sizeof(arr) / sizeof(arr[0]),&matrixColSize,&returnSize,&returnColumnSizes);
	int i,j;
	for(i=0;i<returnSize;++i){
		for(j=0;j<returnColumnSizes[i];++j)
			printf("%d ",ret[i][j]);
		free(ret[i]);
		printf("\n");
	}
	free(returnColumnSizes);
	free(ret);
	return 0;
}
