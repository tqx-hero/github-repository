//
// Created by Administrator on 2026/7/14.
//
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRING_SIZE 21
#define MAX_ARRAY_SIZE 5001

typedef struct {
    int size, index;
    char **urlArray;
} BrowserHistory;


BrowserHistory *browserHistoryCreate(char *homepage) {
    char **array = calloc(1,MAX_ARRAY_SIZE);
    BrowserHistory *bro = malloc(sizeof(BrowserHistory));
    char *url = malloc(strlen(homepage) + 1);
    if (!array || !bro || !url) {
        printf("%s\n", strerror(errno));
        free(array);
        free(bro);
        free(url);
        return NULL;
    }
    bro->size = 1;
    bro->index = 0;
    bro->urlArray = array;
    strcpy(url, homepage);
    bro->urlArray[bro->index++] = url;
    return bro;
}

void freeBoundSpace(int begin, BrowserHistory *obj) {
    if (!obj || !obj->urlArray)
        return;
    //释放这一段内存区域的空间
    int end = obj->size - 1;
    for (int i = begin; i <= end; i++) {
        free(obj->urlArray[i]);
        obj->urlArray[i] = NULL;
    }
}

void browserHistoryVisit(BrowserHistory *obj, char *url) {
    char *urls = malloc(strlen(url) + 1);
    if (!urls) {
        printf("%s\n", strerror(errno));
        return;
    }
    strcpy(urls, url);
    int index = obj->index;
    char *temp = obj->urlArray[index];
    if (temp)
        free(temp);
    obj->urlArray[obj->index++] = urls;
    freeBoundSpace(index + 1, obj);
    obj->size = obj->index;
}

static inline int max(int x, int y) {
    return x >= y ? x : y;
}

static inline int min(int x, int y) {
    return x <= y ? x : y;
}

char *browserHistoryBack(BrowserHistory *obj, int steps) {
    obj->index = max(obj->index - 1 - steps, 0);
    return obj->urlArray[obj->index++];
}

char *browserHistoryForward(BrowserHistory *obj, int steps) {
    obj->index = min(obj->index - 1 + steps, obj->size - 1);
    return obj->urlArray[obj->index++];
}

void browserHistoryFree(BrowserHistory *obj) {
    for (int i = 0; i < obj->size; i++) {
        char *released;
        if (released = obj->urlArray[i]) {
            free(released);
            obj->urlArray[i] = NULL;
        }
    }
}

int main() {
    /*["BrowserHistory","visit","visit","back","visit","forward","visit","visit","forward","visit","back","visit","visit","forward"]
￼
[["esgriv.com"],["cgrt.com"],["tip.com"],[9],["kttzxgh.com"],[7],["crqje.com"],["iybch.com"],[5],["uun.com"],[10],["hci.com"],["whula.com"],[10]]*/
    return 0;
}
