//
// Created by Administrator on 2026/8/7.
//
/**
* 面试题 03.01. 三合一
简单
相关标签
premium lock icon
相关企业
提示
三合一。描述如何只用一个数组来实现三个栈。

你应该实现push(stackNum, value)、pop(stackNum)、isEmpty(stackNum)、peek(stackNum)方法。stackNum表示栈下标，value表示压入的值。

构造函数会传入一个stackSize参数，代表每个栈的大小。

示例 1：

 输入：
["TripleInOne", "push", "push", "pop", "pop", "pop", "isEmpty"]
[[1], [0, 1], [0, 2], [0], [0], [0], [0]]
 输出：
[null, null, null, 1, -1, -1, true]
说明：当栈为空时`pop, peek`返回-1，当栈满时`push`不压入元素。
示例 2：

 输入：
["TripleInOne", "push", "push", "push", "pop", "pop", "pop", "peek"]
[[2], [0, 1], [0, 2], [0, 3], [0], [0], [0], [0]]
 输出：
[null, null, null, null, 2, 1, -1, -1]


提示：

0 <= stackNum <= 2
 * @return
 */

class TripleInOne {
    int *stack_array, every_size;

    struct StackEntry {
        int beginIdx, curIdx;

        explicit StackEntry(int begin_idx, int cur_idx)
            : beginIdx(begin_idx),
              curIdx(cur_idx) {
        }
    };

    StackEntry entry_array[3];

public:
    TripleInOne(int stackSize) : every_size(stackSize),
                                 entry_array{
                                     StackEntry{0, -1},
                                     StackEntry{stackSize, stackSize - 1},
                                     StackEntry{2 * stackSize, 2 * stackSize - 1}
                                 } {
        stack_array = new int[3 * stackSize];
    }


    bool isEmpty(int stackNum) {
        auto &entry = entry_array[stackNum];
        return entry.curIdx + 1 == entry.beginIdx;
    }

    void push(int stackNum, int value) {
        auto &entry = entry_array[stackNum];
        //是否已满
        if (entry.curIdx + 1 - entry.beginIdx == every_size)
            return;
        stack_array[++entry.curIdx] = value;
    }

    int pop(int stackNum) {
        if (isEmpty(stackNum))
            return -1;
        return stack_array[entry_array[stackNum].curIdx--];
    }

    int peek(int stackNum) {
        if (isEmpty(stackNum))
            return -1;
        return stack_array[entry_array[stackNum].curIdx];
    }


    ~TripleInOne() {
        delete[] stack_array;
    }
};

// int main() {
//     return 0;
// }
