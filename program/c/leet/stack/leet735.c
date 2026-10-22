//
// Created by Administrator on 2026/6/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
*
代码
测试用例
测试用例
测试结果
735. 小行星碰撞
中等
相关标签
premium lock icon
相关企业
提示
给定一个整数数组 asteroids，表示在同一行的小行星。数组中小行星的索引表示它们在空间中的相对位置。

对于数组中的每一个元素，其绝对值表示小行星的大小，正负表示小行星的移动方向（正表示向右移动，负表示向左移动）。每一颗小行星以相同的速度移动。

找出碰撞后剩下的所有小行星。碰撞规则：两个小行星相互碰撞，较小的小行星会爆炸。如果两颗小行星大小相同，则两颗小行星都会爆炸。两颗移动方向相同的小行星，永远不会发生碰撞。



示例 1：

输入：asteroids = [5,10,-5]
输出：[5,10]
解释：10 和 -5 碰撞后只剩下 10 。 5 和 10 永远不会发生碰撞。
示例 2：

输入：asteroids = [8,-8]
输出：[]
解释：8 和 -8 碰撞后，两者都发生爆炸。
示例 3：

输入：asteroids = [10,2,-5]
输出：[10]
解释：2 和 -5 发生碰撞后剩下 -5 。10 和 -5 发生碰撞后剩下 10 。
示例 4：

输入：asteroids = [3,5,-6,2,-1,4]
输出：[-6,2,4]
解释：小行星 -6 使小行星 3 和 5 爆炸，然后继续向左移动。在另一边，小行星 2 使小行星 -1 爆炸，然后继续向右移动，没有碰撞小行星 4。


提示：

2 <= asteroids.length <= 104
-1000 <= asteroids[i] <= 1000
asteroids[i] != 0
 * @return
 */
//用栈。
//顺序压栈。栈内元素符号相同，要么都为负，要么都为正
//压入第一个数字，指针从第二个元素a开始。
//每次与栈顶元素b比较。
//1、先比较符号，可以用a^b>0来判断与栈顶元素是否为同一符号。
//如果是同一符号，直接入栈，指针++；如果符号不同：
//比较a与b的大小。令c=a+b，然后a^c >0，判断结果是否为正,为正表示与a元素相同，即a绝对值大，弹栈
//迭代：a继续与栈顶比较，因为栈内元素符号相同，所以只比较绝对值大小即可，如果a绝对值还大，继续弹栈...
//直到栈空，这时候查看a的值是大于0还是小于0，如果大于0，入栈。小于0，放入结果数组。
//如果栈没空时，a绝对值比栈顶小了，那就停止弹栈，丢弃a
//以上步骤执行完成后，指针都会++。
//最后的结果就是结果集内已存在的数据为负数，栈内的结果为相同符号，要么都为正，要么都为负。
//最后把栈内元素从头到位遍历拼接到结果集后面即可

#define STACK_MAX_SIZE 100001
#define STACK Stack *
#define STACK_PTR(name) STACK name
#define SHR31(param) ((param)>>31)

//
typedef struct Stack {
    int arr[STACK_MAX_SIZE];
    int ptr;
    //可选函数指针
    // int (*func_ptr)(int *, ...);
} Stack;

void init(STACK_PTR(this)) {
    this->ptr = -1;
}

int size(STACK_PTR(this)) {
    return this->ptr + 1;
}

void push(STACK_PTR(this), int x) {
    this->arr[++this->ptr] = x;
}

_Bool isEmpty(STACK_PTR(this)) {
    return this->ptr == -1;
}

int pop(STACK_PTR(this)) {
    return this->arr[this->ptr--];
}


int peek(STACK_PTR(this)) {
    return this->arr[this->ptr];
}

int *asteroidCollision(int *asteroids, int asteroidsSize, int *returnSize) {
    int *ret = calloc(asteroidsSize, sizeof(int));
    if (!ret) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    Stack stack = {};
    init(&stack);
    int i = 0, count = 0;
    for (; i < asteroidsSize; ++i) {
        int num = *(asteroids + i);
        while (true) {
            //如果栈为空，需要判断num大于0还是小于0
            if (isEmpty(&stack)) {
                //大于0，入栈；小于0，入结果集
                if (num > 0)
                    push(&stack, num);
                else
                    *(ret + count++) = num;
                break;
            }

            int top = peek(&stack);
            //符号相同，入栈
            if (!(SHR31(num ^ top) & 0x1)) {
                push(&stack, num);
                break;
            }
            //不同，查看哪个绝对值大
            int mm = num + top;
            //之和为0，绝对值一样大，弹栈并跳出循环
            if (!mm) {
                pop(&stack);
                break;
                //与num符号相同，弹栈，继续循环
            }
            if (!(SHR31(mm ^ num) & 0x1))
                pop(&stack);
            else
                //与num符号不同，说明栈顶比num大，直接舍弃num
                break;
        }
    }
    //结束后遍历栈，追加到结果集后面
    int sz = size(&stack);
    for (i = 0; i < sz; ++i, count++)
        *(ret + count) = *(stack.arr + i);
    *returnSize = count;
    return ret;
}

int main() {
    int arr[] = {5, 10, -5};
    // int arr[] = {3, 5, -6, 2, -1, 4};
    int size;
    int *res = asteroidCollision(arr, sizeof(arr) / sizeof(int), &size);
    for (int i = 0; i < size; ++i)
        printf("%d ", res[i]);
    free(res);
    return 0;
}
