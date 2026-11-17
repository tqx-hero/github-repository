/**
1287. 有序数组中出现次数超过25%的元素
简单
相关标签
premium lock icon
相关企业
提示
给你一个非递减的 有序 整数数组，已知这个数组中恰好有一个整数，它的出现次数超过数组元素总数的 25%。

请你找到并返回这个整数

 

示例：

输入：arr = [1,2,2,6,6,6,6,7,10]
输出：6
 

提示：

1 <= arr.length <= 10^4
0 <= arr[i] <= 10^5
  */
#include <stdio.h>
#include <stdlib.h>

int findSpecialInteger(int* arr, int arrSize) {
    int targetcnt = arrSize / 4;
    int cnt = 1,i;
    for( i = 1 ; i < arrSize ; ++i ){
        if(arr[i] == arr[i - 1])
            cnt++;
        else{
            if(cnt > targetcnt)
                return arr[i - 1];
            cnt = 1;
        }
    }
    return arr[arrSize - 1];
}

int main(){
    int arr[] = {1,2,3,3};

    exit(0);
}
