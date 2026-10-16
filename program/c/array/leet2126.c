//
// Created by Administrator on 2026/6/18.
//
/**
* 2126. 摧毁小行星
中等
相关标签
premium lock icon
相关企业
提示
给你一个整数 mass ，它表示一颗行星的初始质量。再给你一个整数数组 asteroids ，其中 asteroids[i] 是第 i 颗小行星的质量。

你可以按 任意顺序 重新安排小行星的顺序，然后让行星跟它们发生碰撞。如果行星碰撞时的质量 大于等于 小行星的质量，那么小行星被 摧毁 ，并且行星会 获得 这颗小行星的质量。否则，行星将被摧毁。

如果所有小行星 都 能被摧毁，请返回 true ，否则返回 false 。



示例 1：

输入：mass = 10, asteroids = [3,9,19,5,21]
输出：true
解释：一种安排小行星的方式为 [9,19,5,3,21] ：
- 行星与质量为 9 的小行星碰撞。新的行星质量为：10 + 9 = 19
- 行星与质量为 19 的小行星碰撞。新的行星质量为：19 + 19 = 38
- 行星与质量为 5 的小行星碰撞。新的行星质量为：38 + 5 = 43
- 行星与质量为 3 的小行星碰撞。新的行星质量为：43 + 3 = 46
- 行星与质量为 21 的小行星碰撞。新的行星质量为：46 + 21 = 67
所有小行星都被摧毁。
示例 2：

输入：mass = 5, asteroids = [4,9,23,4]
输出：false
解释：
行星无论如何没法获得足够质量去摧毁质量为 23 的小行星。
行星把别的小行星摧毁后，质量为 5 + 4 + 9 + 4 = 22 。
它比 23 小，所以无法摧毁最后一颗小行星。


提示：

1 <= mass <= 105
1 <= asteroids.length <= 105
1 <= asteroids[i] <= 105
 * @return
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int cap;
} MinHeap;

static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

bool isEmpty(MinHeap *heap) {
    return heap->size == 0;
}

MinHeap *heapInit(int cap) {
    MinHeap *h = malloc(sizeof(MinHeap));
    h->data = malloc(cap * sizeof(int));
    h->size = 0;
    h->cap = cap;
    return h;
}

static void up(MinHeap *h, int idx) {
    while (idx > 0) {
        int p = (idx - 1) / 2;
        if (h->data[idx] >= h->data[p]) break;
        swap(&h->data[idx], &h->data[p]);
        idx = p;
    }
}

static void down(MinHeap *h, int idx) {
    int n = h->size;
    while (1) {
        int l = 2 * idx + 1, r = 2 * idx + 2, t = idx;
        if (l < n && h->data[l] < h->data[t]) t = l;
        if (r < n && h->data[r] < h->data[t]) t = r;
        if (t == idx) break;
        swap(&h->data[idx], &h->data[t]);
        idx = t;
    }
}

void push(MinHeap *h, int x) {
    if (h->size >= h->cap) return;
    h->data[h->size++] = x;
    up(h, h->size - 1);
}

bool pop(MinHeap *h, int *out) {
    if (h->size == 0) return 0;
    *out = h->data[0];
    h->data[0] = h->data[--h->size];
    down(h, 0);
    return 1;
}

void heapFree(MinHeap *h) {
    free(h->data);
    free(h);
}

//遍历数组，当出现比当前值大的数据，放入小顶堆，小于等于当前值的，就与cur相加，更新cur为这个和，继续遍历，直到结束
//遍历小顶堆，如果出现堆顶大于cur值的返回false，堆清空返回true
bool asteroidsDestroyed(int mass, int *asteroids, int asteroidsSize) {
    long long cur = mass;
    MinHeap *heap = heapInit(asteroidsSize << 2);
    int i = 0;
    for (; i < asteroidsSize; i++) {
        int val = asteroids[i];
        if (val <= cur)
            cur += val;
        else
            push(heap, val);
    }
    //遍历小顶堆
    while (!isEmpty(heap)) {
        int top;
        pop(heap, &top);
        if (top > cur) {
            free(heap);
            return false;
        }
        cur += top;
    }
    free(heap);
    return true;
}

int main() {
    // int mass = 10, asteroids[] = {3,9,19,5,21};
    int mass = 5, asteroids[] = {4, 9, 23, 4};
    printf("%d\n", asteroidsDestroyed(mass, asteroids, sizeof(asteroids) / sizeof(int)));

    return 0;
}
