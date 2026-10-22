//
// Created by Administrator on 2026/6/22.
//
/**
* Q1. 用栈操作构建数组
中等
相关标签
premium lock icon
相关企业
提示
给你一个数组 target 和一个整数 n。

给你一个空栈和两种操作：

"Push"：将一个整数加到栈顶。
"Pop"：从栈顶删除一个整数。
同时给定一个范围 [1, n] 中的整数流。

使用两个栈操作使栈中的数字（从底部到顶部）等于 target。你应该遵循以下规则：

如果整数流不为空，从流中选取下一个整数并将其推送到栈顶。
如果栈不为空，弹出栈顶的整数。
如果，在任何时刻，栈中的元素（从底部到顶部）等于 target，则不要从流中读取新的整数，也不要对栈进行更多操作。
请返回遵循上述规则构建 target 所用的操作序列。如果存在多个合法答案，返回 任一 即可。



示例 1：

输入：target = [1,3], n = 3
输出：["Push","Push","Pop","Push"]
解释：一开始栈为空。最后一个元素是栈顶。
从流中读取 1 并推入数组。s = [1]。
从流中读取 2 并推入数组。s = [1,2]。
从栈顶删除整数。s = [1]。
从流中读取 3 并推入数组。s = [1,3]。
示例 2：

输入：target = [1,2,3], n = 3
输出：["Push","Push","Push"]
解释：一开始栈为空。最后一个元素是栈顶。
从流中读取 1 并推入数组。s = [1]。
从流中读取 2 并推入数组。s = [1,2]。
从流中读取 3 并推入数组。s = [1,2,3]。
示例 3：

输入：target = [1,2], n = 4
输出：["Push","Push"]
解释：一开始栈为空。最后一个元素是栈顶。
从流中读取 1 并推入数组。s = [1]。
从流中读取 2 并推入数组。s = [1,2]。
由于栈（从底部到顶部）等于 target，我们停止栈操作。
从流中读取整数 3 的答案不被接受。


提示：

1 <= target.length <= 100
1 <= n <= 100
1 <= target[i] <= n
target 严格递增
 * @return
 */

#define STACK_MAX_SIZE 101
#define STACKPTR(name) Stack* name
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//
typedef struct Stack {
    int arr[STACK_MAX_SIZE];
    int ptr;
    //可选函数指针
} Stack;

void init(STACKPTR(this)) {
    this->ptr = -1;
}

void push(STACKPTR(this), int x) {
    this->arr[++this->ptr] = x;
}

bool isEmpty(STACKPTR(this)) {
    return this->ptr == -1;
}

int pop(STACKPTR(this)) {
    return this->arr[this->ptr--];
}


int peek(STACKPTR(this)) {
    return this->arr[this->ptr];
}

char **buildArray(int *target, int targetSize, int n, int *returnSize) {
    Stack stack = {};
    init(&stack);
    char *pushed = "Push";
    char *poped = "Pop";
    char **ret = (char **) malloc(2 * n * sizeof(pushed));
    int i = 0, ni = 1, ret_index = 0;
    for (; i < targetSize;) {
        push(&stack, ni);
        ret[ret_index++] = pushed;
        //如果两者相同，指针后移
        if (target[i] == ni) {
            ni++;
            i++;
        }
        //如果两者不同，则需要弹出栈顶，ni++，i不变，同时记录操作到ret
        else {
            pop(&stack);
            ret[ret_index++] = poped;
            ni++;
        }
    }
    *returnSize = ret_index;
    return ret;
}

int main() {
    int target[] = {1,2}, n = 4, size;
    char **ret = buildArray(target, sizeof(target) / sizeof(int), n, &size);
    int i=0;
    for (;i<size;i++) {
        printf("%s ",ret[i]);
    }
    free(ret);
    return 0;
}
