// //
// // Created by Administrator on 2026/6/27.
// //
// /**
// * 341. 扁平化嵌套列表迭代器
// 中等
// 相关标签
// premium lock icon
// 相关企业
// 给你一个嵌套的整数列表 nestedList 。每个元素要么是一个整数，要么是一个列表；该列表的元素也可能是整数或者是其他列表。请你实现一个迭代器将其扁平化，使之能够遍历这个列表中的所有整数。
//
// 实现扁平迭代器类 NestedIterator ：
//
// NestedIterator(List<NestedInteger> nestedList) 用嵌套列表 nestedList 初始化迭代器。
// int next() 返回嵌套列表的下一个整数。
// boolean hasNext() 如果仍然存在待迭代的整数，返回 true ；否则，返回 false 。
// 你的代码将会用下述伪代码检测：
//
// initialize iterator with nestedList
// res = []
// while iterator.hasNext()
//     append iterator.next() to the end of res
// return res
// 如果 res 与预期的扁平化列表匹配，那么你的代码将会被判为正确。
//
//
//
// 示例 1：
//
// 输入：nestedList = [[1,1],2,[1,1]]
// 输出：[1,1,2,1,1]
// 解释：通过重复调用 next 直到 hasNext 返回 false，next 返回的元素的顺序应该是: [1,1,2,1,1]。
// 示例 2：
//
// 输入：nestedList = [1,[4,[6]]]
// 输出：[1,4,6]
// 解释：通过重复调用 next 直到 hasNext 返回 false，next 返回的元素的顺序应该是: [1,4,6]。
//
//
// 提示：
//
// 1 <= nestedList.length <= 500
// 嵌套列表中的整数值在范围 [-106, 106] 内
//  * @return
//  */
//
// #include <stdbool.h>
// #include <stdlib.h>
//
// /**
//  * *********************************************************************
//  * // This is the interface that allows for creating nested lists.
//  * // You should not implement it, or speculate about its implementation
//  * *********************************************************************
//  *
//  * // Return true if this NestedInteger holds a single integer, rather than a nested list.
//  * bool NestedIntegerIsInteger(struct NestedInteger *);
//  *
//  * // Return the single integer that this NestedInteger holds, if it holds a single integer
//  * // The result is undefined if this NestedInteger holds a nested list
//  * int NestedIntegerGetInteger(struct NestedInteger *);
//  *
//  * // Return the nested list that this NestedInteger holds, if it holds a nested list
//  * // The result is undefined if this NestedInteger holds a single integer
//  * struct NestedInteger **NestedIntegerGetList(struct NestedInteger *);
//  *
//  * // Return the nested list's size that this NestedInteger holds, if it holds a nested list
//  * // The result is undefined if this NestedInteger holds a single integer
//  * int NestedIntegerGetListSize(struct NestedInteger *);
//  * };
//  */
//
// struct NestedInteger {
//
// };
//
// bool NestedIntegerIsInteger(struct NestedInteger *nums) {
//     return true;
// }
// int NestedIntegerGetInteger(struct NestedInteger * nums) {
//     return 0;
// }
// // {
// //
// // }
//
//
// //这里必须为2的整数幂
// #define MAX_SIZE 512
//
//
// //定义一个循环队列
// typedef struct ArrayDeque {
//     int obj[MAX_SIZE];
//     int count;
//     int front;
//     int rear;
// } ArrayDeque;
//
// _Bool isEmpty(ArrayDeque *queue) {
//     return queue->count == 0;
// }
//
// void initQueue(ArrayDeque *queue) {
//     queue->count = 0;
//     queue->rear = 0;
//     queue->front = 0;
// }
//
// int poll(ArrayDeque *queue) {
//     if (!isEmpty(queue)) {
//         int obj = queue->obj[queue->front];
//         queue->count--;
//         queue->front = (queue->front + 1) & (MAX_SIZE - 1);
//         return obj;
//     }
//     return -1;
// }
//
// int peek(ArrayDeque *queue) {
//     if (!isEmpty(queue))
//         return queue->obj[queue->front];
//     return -1;
// }
//
// _Bool isFull(ArrayDeque *queue) {
//     return queue->count == MAX_SIZE;
// }
//
// int size(ArrayDeque *queue) {
//     return queue->count;
// }
//
// int offer(ArrayDeque *queue, int obj) {
//     if (!isFull(queue)) {
//         queue->obj[queue->rear] = obj;
//         queue->rear = (queue->rear + 1) & (MAX_SIZE - 1);
//         queue->count++;
//         return 1;
//     }
//     return 0;
// }
//
// struct NestedIterator {
//     int curIndex, intIndex, nestedListSize;
//     struct NestedInteger **nestedList;
//     ArrayDeque queue;
// };
//
// struct NestedIterator *nestedIterCreate(struct NestedInteger **nestedList, int nestedListSize) {
//     struct NestedIterator *it = malloc(sizeof(struct NestedIterator));
//     it->curIndex = 0;
//     it->intIndex = 0;
//     it->nestedListSize = nestedListSize;
//     it->nestedList = nestedList;
//     initQueue(&it->queue);
//     //加载队列
//     int i = 0;
//     for (; i < nestedListSize; i++) {
//         struct NestedInteger *nums = nestedList[i];
//         while (!isFull(&it->queue)) {
//             if (NestedIntegerIsInteger(nums)) {
//                 offer(&it->queue, NestedIntegerGetInteger(nums));
//                 break;
//             }
//             //如果不是一个整数，那就是一个嵌套列表
//
//         }
//     }
// }
//
// bool nestedIterHasNext(struct NestedIterator *iter) {
// }
//
// int nestedIterNext(struct NestedIterator *iter) {
// }
//
// /** Deallocates memory previously allocated for the iterator */
// void nestedIterFree(struct NestedIterator *iter) {
//     iter->nestedList = NULL;
//     free(iter);
//     iter = NULL;
// }
//
// int main() {
//     return 0;
// }
