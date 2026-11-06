/**
997. 找到小镇的法官
简单
相关标签
premium lock icon
相关企业
小镇里有 n 个人，按从 1 到 n 的顺序编号。传言称，这些人中有一个暗地里是小镇法官。

如果小镇法官真的存在，那么：

小镇法官不会信任任何人。
每个人（除了小镇法官）都信任这位小镇法官。
只有一个人同时满足属性 1 和属性 2 。
给你一个数组 trust ，其中 trust[i] = [ai, bi] 表示编号为 ai 的人信任编号为 bi 的人。

如果小镇法官存在并且可以确定他的身份，请返回该法官的编号；否则，返回 -1 。

 

示例 1：

输入：n = 2, trust = [[1,2]]
输出：2
示例 2：

输入：n = 3, trust = [[1,3],[2,3]]
输出：3
示例 3：

输入：n = 3, trust = [[1,3],[2,3],[3,1]]
输出：-1
 
提示：

1 <= n <= 1000
0 <= trust.length <= 104
trust[i].length == 2
trust 中的所有trust[i] = [ai, bi] 互不相同
ai != bi
1 <= ai, bi <= n
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *Calloc(size_t cnt,size_t size){
	int *ret;
	if((ret = calloc(cnt,size)) == NULL){
		perror("malloc() error");
		exit(1);
	}
	return ret;
}

int findJudge(int n, int** trust, int trustSize, int* trustColSize) {
	int ret,i;
	int *cache;
	cache = Calloc(n + 1, sizeof(int));
	for(i = 0;i < trustSize;++i)
		cache[trust[i][0]]++;
	//如果都出现过投票，无法确定
	for(i = 1;i <= n && cache[i];++i);
	if(i > n)
		return -1;
	ret = i;
	memset(cache,0,sizeof(int) * (n + 1));
	//再次统计第二次的次数
	for(i = 0;i < trustSize;++i)
		cache[trust[i][1]]++;
	for(i = 1;i <= n && cache[i] < n - 1;++i);
	free(cache);
	return i  == ret ? i : -1;
}

int main(){
//	int  t1[] = {1,3},t2[] = {2,3};
	//[[1,3],[2,3],[3,1]]
	//[[1,3],[1,4],[2,3],[2,4],[4,3]]
	int  t1[] = {1,3},t2[] = {1,4},t3[] = {2,3},t4[] = {2,4}, t5[] = {4,3};
	int n = 4, *trust[] = {t1,t2,t3,t4,t5},colSize = sizeof(t1) / sizeof(int);
	fprintf(stdout,"%d\n",findJudge(n,trust,sizeof(trust) / sizeof(int*) , &colSize));
	return 0;
}
