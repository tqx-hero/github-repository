/**
 *566. 重塑矩阵
简单
相关标签
premium lock icon
相关企业
提示
在 MATLAB 中，有一个非常有用的函数 reshape ，它可以将一个 m x n 矩阵重塑为另一个大小不同（r x c）的新矩阵，但保留其原始数据。

给你一个由二维数组 mat 表示的 m x n 矩阵，以及两个正整数 r 和 c ，分别表示想要的重构的矩阵的行数和列数。

重构后的矩阵需要将原始矩阵的所有元素以相同的 行遍历顺序 填充。

如果具有给定参数的 reshape 操作是可行且合理的，则输出新的重塑矩阵；否则，输出原始矩阵。

 

示例 1：


输入：mat = [[1,2],[3,4]], r = 1, c = 4
输出：[[1,2,3,4]]
示例 2：


输入：mat = [[1,2],[3,4]], r = 2, c = 4
输出：[[1,2],[3,4]]
 

提示：

m == mat.length
n == mat[i].length
1 <= m, n <= 100
-1000 <= mat[i][j] <= 1000
1 <= r, c <= 300
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void memset_int(int* returnCol,int val,int size){
	int i=0;
	while(i < size)
		returnCol[i++] = val;
}

int** matrixReshape(int** mat, int matSize, int* matColSize, int r, int c, int* returnSize, int** returnColumnSizes) {
	int **ret;
	ret = (int**)malloc(matSize * (*matColSize) * sizeof(int));
	memcpy(ret,mat,sizeof(int) * matSize * (*matColSize));
	//如果个数不匹配，直接申请原数组大小，填充
	if(matSize * (*matColSize) != r * c){
		*returnColumnSizes =(int*) malloc(matSize * sizeof(int));
		*returnSize = matSize;
		//拷贝整型值到数组
		memset_int(*returnColumnSizes,*matColSize,matSize);
		return ret;
	}
	//个数匹配
	*returnSize = r;
	*returnColumnSizes = (int*) malloc(r * sizeof(int));
	memset_int(*returnColumnSizes, c , r);
	return ret;
}

int main(){
	//mat = [[1,2],[3,4]], r = 1, c = 4
	int m1[] = {1,2},m2[] = {3,4};
	int *mat[] = {
		m1,m2
	},r =1,c= 4;
	int matColSize = 2,returnSize;
	int * returnColumnSizes;
	int ** ret = matrixReshape(mat,sizeof(mat) / sizeof(mat[0]),&matColSize,r,c,&returnSize,&returnColumnSizes);
	int i,j;
	for(i=0;i<returnSize;++i){
		for(j=0;j<returnColumnSizes[i];++j){
			printf("%d ",ret[i][j]);
		}
		printf("\n");
	}
	free((void*)returnColumnSizes);
	free((void*)ret);
	return 0;
}
