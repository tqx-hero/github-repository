
/**
989. 数组形式的整数加法
简单
相关标签
premium lock icon
相关企业
整数的 数组形式  num 是按照从左到右的顺序表示其数字的数组。

例如，对于 num = 1321 ，数组形式是 [1,3,2,1] 。
给定 num ，整数的 数组形式 ，和整数 k ，返回 整数 num + k 的 数组形式 。

 

示例 1：

输入：num = [1,2,0,0], k = 34
输出：[1,2,3,4]
解释：1200 + 34 = 1234
示例 2：

输入：num = [2,7,4], k = 181
输出：[4,5,5]
解释：274 + 181 = 455
示例 3：

输入：num = [2,1,5], k = 806
输出：[1,0,2,1]
解释：215 + 806 = 1021
 

提示：

1 <= num.length <= 104
0 <= num[i] <= 9
num 不包含任何前导零，除了零本身
1 <= k <= 104
  */
#include <stdio.h>
#include <stdlib.h>

int *Malloc(size_t size){
	int *ret;
	if(!(ret = malloc(size))){
		perror("malloc() error");
		exit(1);
	}
	return ret;
}

void update_ret(int *ret,int reti,int *remain,int temp){
	if(temp > 9){
		ret[reti] = temp - 10;
		*remain = 1;
	}else{
		ret[reti] = temp;
		*remain = 0;
	}
}

int* addToArrayForm(int* num, int numSize, int k, int* returnSize) {
	int *ret,i,remain,tempn,reti;
	ret = Malloc(10001 * sizeof(int));
	remain = 0;
	reti = 0;
	for(i = numSize - 1;i  >= 0 && (k || remain);--i,++reti){
		//如果k值不为0，或者有进位，继续执行
		tempn = num[i] + remain + k % 10;
		update_ret(ret,reti,&remain,tempn);
		k /= 10; 
	}
	//看哪个加完了，是数组加完了还是k加完了
	//k还不为0，数组加完了，那就把k逐一加到数组
	if(k){
	while(k || remain){
		tempn = k % 10 + remain;
		update_ret(ret,reti,&remain,tempn);
		++reti;
		k /= 10;
	}
	}else if(i >= 0){//如果i还没到头，就继续加
		int tmp;
		for(;i >= 0 || remain;--i,++reti){
			if(i >= 0){
				tmp = num[i];
			}else
				tmp = 0;
			tempn = tmp + remain;
			update_ret(ret,reti,&remain,tempn);
		}
	}
	if(remain)
		ret[reti++] = remain;
	//翻转数组
	int left,right;
	for(left = 0,right = reti - 1;left < right;++left,--right){
		int temp = ret[left];
		ret[left] = ret[right];
		ret[right] = temp;
	}
	*returnSize = reti;
	return ret;
}

int main(){
//	int num[] = {1,2,0,0}, k = 34,returnSize;
	//num = [2,1,5], k = 806
	int num[] = {2,1,5}, k = 806,returnSize;
	int *ret = addToArrayForm(num,sizeof(num) / sizeof(int) , k , &returnSize);
	for(int i = 0;i < returnSize;++i)
		fprintf(stdout,"%d ",ret[i]);
	fprintf(stdout,"\n");
	free(ret);
	return 0;
}
