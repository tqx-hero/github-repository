//
// Created by Administrator on 2026/7/6.
//

/**
* 1288. 删除被覆盖区间
中等
相关标签
premium lock icon
相关企业
提示
给你一个区间列表，请你删除列表中被其他区间所覆盖的区间。

只有当 c <= a 且 b <= d 时，我们才认为区间 [a,b) 被区间 [c,d) 覆盖。

在完成所有删除操作后，请你返回列表中剩余区间的数目。



示例：

输入：intervals = [[1,4],[3,6],[2,8]]
输出：2
解释：区间 [3,6] 被区间 [2,8] 覆盖，所以它被删除了。


提示：​​​​​​

1 <= intervals.length <= 1000
0 <= intervals[i][0] < intervals[i][1] <= 10^5
对于所有的 i != j：intervals[i] != intervals[j]
 * @return
 */
//先排序，按照区间的左侧，升序排列
//遍历数组，先查看左区间值是否相等，相等则比较右侧值，保留大的，去掉小的
//不相等，比较区间右侧值大小，若i<j，且arr[i][1]> arr[j][1]，即右侧值小于等于之前的那个值，即出现包含关系，不记录j
//如果大于，不包括，添加这条记录。
//记录的保存形式可以放到栈里面，这样在遍历数组时只与栈顶比较即可
//因为排序后的每个子数组都满足一个条件：
//每个区间的左侧全部升序排列，即下标i<j，arr[i][0]<=arr[j][0],如果值相同，那就比较arr[i][1],arr[j][1],右侧大的包含小的
//如果不相同，那必然arr[i][0] <arr[j][0],这是升序排列后的结果，这时如果区间右侧值，j的小于等与i的，那必然被i区间包裹，大于则必然不会被包裹
//假设不会被包裹，栈内则会有2条记录：[i,a) 、[j,b),后续如果出现[k,c),k必然大于等于j,此时比较b与c，c<=b必然被[j,b)包裹，那如果c>b,由于a<b,必然c>a,
//更不可能被[i,a)包裹，所以只需要与栈顶那个记录比较即可得出结果，结果也不会漏


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int compare(const void *a, const void *b) {
    return **(int **) a - **(int **) b;
}

int removeCoveredIntervals(int **intervals, int intervalsSize, int *intervalsColSize) {
    int ret = 0;
    if (intervalsSize == 1) {
        ret = 1;
        goto ret_func;
    }
    qsort(intervals, intervalsSize, (*intervalsColSize) * sizeof(int), compare);
    //申请栈空间，用来存放数组的下标
    int *idx_arr = malloc(intervalsSize * sizeof(int));
    if (!idx_arr) {
        printf("%s\n", strerror(errno));
        goto ret_func;
    }
    for (int i = 0; i < intervalsSize; i++) {
        //如果栈不为空，拿出栈顶元素，即数组下标，与它的左右区间比较
        if (ret) {
            int *interval = intervals[idx_arr[ret - 1]];
            //区间左侧相同，比较右侧，右侧大于栈顶的，替换栈顶元素，否则丢弃
            if (intervals[i][0] == interval[0] && intervals[i][1] > interval[1])
                idx_arr[ret - 1] = i;
                //大于左侧，且大于右侧，需要添加到栈内,小于等于时同样丢弃
            else if (intervals[i][0] > interval[0] && intervals[i][1] > interval[1])
                idx_arr[ret++] = i;
        } else
            idx_arr[ret++] = i;
    }
    free(idx_arr);
ret_func:
    return ret;
}

int main() {
    //[[1,4],[3,6],[2,8]]
    int arr1[] = {1, 4};
    int arr2[] = {3, 6};
    int arr3[] = {2, 8};
    int *intervals[] = {arr1, arr2, arr3}, colSize = 2;
    printf("%d\n", removeCoveredIntervals(intervals, sizeof(intervals) / sizeof(intervals[0]), &colSize));
    return 0;
}
