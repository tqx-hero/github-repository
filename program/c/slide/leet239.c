#include <stdio.h>
#include <stdlib.h>
//
// Created by Administrator on 2026/6/11.
//
/**
* 239. 滑动窗口最大值
困难
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回 滑动窗口中的最大值 。



示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：

输入：nums = [1], k = 1
输出：[1]


提示：

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
 * @return
 */
//用单调队列
//分析：
//如果下标靠后的数据比窗口中它前面的数据都大的话，那窗口往后滑动，前面的数据不可能再成为窗口的最大值
//因为最大值的下标都大于它们，下标更大就意味着在窗口中的时间比前面的更长
//所以前面的小数据都可以舍弃
//如果窗口新出的数据比前面的值小的话，那就需要记录下来，因为更大值的下标更小，会更早的滑出窗口
//那后面的这个较小值就有可能成为最大值。
//所以需要用一个队列来记录这些数据
//保证数据的先进先出的特点，同时还需要用这个队列维护最大值，这就是要用单调递减队列
//队列内放数据的下标，同时需注意队头下标弹出窗口的情况
#define MAX_SIZE 100001


//定义一个循环队列
typedef struct ArrayDeque {
    int obj[MAX_SIZE];
    int count;
    int front;
    int rear;
} ArrayDeque;

_Bool isEmpty(ArrayDeque *queue) {
    return queue->count == 0;
}

void initQueue(ArrayDeque *queue) {
    queue->count = 0;
    queue->rear = 0;
    queue->front = 0;
}

int poll(ArrayDeque *queue) {
    if (!isEmpty(queue)) {
        int obj = queue->obj[queue->front];
        queue->count--;
        queue->front = (queue->front + 1) % MAX_SIZE;
        return obj;
    }
    return -1;
}

int pollLast(ArrayDeque *queue) {
    if (!isEmpty(queue)) {
        int obj = queue->obj[--queue->rear];
        queue->count--;
        return obj;
    }
    return -1;
}

int peek(ArrayDeque *queue) {
    if (!isEmpty(queue))
        return queue->obj[queue->front];
    return -1;
}

//取出队尾的值，不弹出
int peekLast(ArrayDeque *queue) {
    if (!isEmpty(queue)) {
        return queue->obj[queue->rear - 1];
    }
    return -1;
}

_Bool isFull(ArrayDeque *queue) {
    return queue->count == MAX_SIZE;
}

int size(ArrayDeque *queue) {
    return queue->count;
}

int offer(ArrayDeque *queue, int obj) {
    if (!isFull(queue)) {
        queue->obj[queue->rear] = obj;
        queue->rear = (queue->rear + 1) % MAX_SIZE;
        queue->count++;
        return 1;
    }
    return 0;
}

int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize) {
    *returnSize = numsSize - k + 1;
    int *ret = calloc(*returnSize, sizeof(int));
    ArrayDeque queue = {};
    initQueue(&queue);
    //加载队列
    int i = 0, resCount = 0;
    for (; i < k; i++) {
        //当前值如果大于等于队尾值，因为下标大，直接poll队尾
        while (!isEmpty(&queue) && nums[peekLast(&queue)] <= nums[i])
            pollLast(&queue);
        offer(&queue, i);
    }
    ret[resCount++] = nums[peek(&queue)];
    int left = 1, right = k;
    for (; right < numsSize; left++, right++, resCount++) {
        //如果队头下标小于left，poll直到大于等于left或者队列为空
        while (!isEmpty(&queue) && peek(&queue) < left)
            poll(&queue);
        while (!isEmpty(&queue) && nums[peekLast(&queue)] <= nums[right])
            pollLast(&queue);
        offer(&queue, right);
        ret[resCount] = nums[peek(&queue)];
    }
    return ret;
}

int main() {
    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int sz;
    int *ret = maxSlidingWindow(arr, 8, 3, &sz);
    for (int i = 0; i < sz; ++i) {
        printf("%d\n", *(ret + i));
    }
    free(ret);
    return 0;
}
