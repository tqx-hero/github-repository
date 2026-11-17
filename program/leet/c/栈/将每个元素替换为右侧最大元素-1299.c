/**
  1299. 将每个元素替换为右侧最大元素
简单
相关标签
premium lock icon
相关企业
提示
给你一个数组 arr ，请你将每个元素用它右边最大的元素替换，如果是最后一个元素，用 -1 替换。

完成所有替换操作后，请你返回这个数组。



示例 1：

输入：arr = [17,18,5,4,6,1]
输出：[18,6,6,6,1,-1]
解释：
- 下标 0 的元素 --> 右侧最大元素是下标 1 的元素 (18)
- 下标 1 的元素 --> 右侧最大元素是下标 4 的元素 (6)
- 下标 2 的元素 --> 右侧最大元素是下标 4 的元素 (6)
- 下标 3 的元素 --> 右侧最大元素是下标 4 的元素 (6)
- 下标 4 的元素 --> 右侧最大元素是下标 5 的元素 (1)
- 下标 5 的元素 --> 右侧没有其他元素，替换为 -1
示例 2：

输入：arr = [400]
输出：[-1]
解释：下标 0 的元素右侧没有其他元素。


提示：

1 <= arr.length <= 104
1 <= arr[i] <= 105
  */
#include <stdio.h>
#include <stdlib.h>
int* replaceElements(int* arr, int arrSize, int* returnSize) {
    int *ret;
    int i,max_surfix;
    if((ret = malloc(arrSize * sizeof(int))) == NULL)
    {
        perror("malloc()");
        exit(1);
    }
    *returnSize = arrSize;
    max_surfix = -1;
    for(i = arrSize - 1 ; i >= 0 ; --i )
    {
        ret[i] = max_surfix;
        if(arr[i] > max_surfix)
            max_surfix = arr[i];
    }
    return ret;
}

int main(){
    int arr[] = {17,18,5,4,6,1},returnSize;
    auto int *arrs = replaceElements(arr,sizeof(arr) / sizeof(int),&returnSize);
    int i = 0;
    for(i = 0;i < returnSize;++i)
        fprintf(stdout,"%d ",arrs[i]);
    fprintf(stdout,"\n");
    free(arrs);
    exit(0);
}
