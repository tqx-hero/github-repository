//
// Created by Administrator on 2026/6/14.
//
#include <stdio.h>
#include <stdlib.h>
#include "minHeap.h"
#include <stdbool.h>
static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
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
