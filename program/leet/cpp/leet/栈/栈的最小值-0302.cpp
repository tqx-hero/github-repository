//
// Created by Administrator on 2026/8/1.
//
/**
* 面试题 03.02. 栈的最小值
简单
相关标签
premium lock icon
相关企业
提示
请设计一个栈，除了常规栈支持的pop与push函数以外，还支持min函数，该函数返回栈元素中的最小值。执行push、pop和min操作的时间复杂度必须为O(1)。


示例：

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
 * @return
 */
#include <stack>
using namespace std;

class MinStack {
    int index;
    stack<pair<int, int> > stack, minStack;

public:
    MinStack() : index(0) {
    }

    void push(int x) {
        pair<int, int> newPair = make_pair(index++, x);
        stack.push(newPair);
        if (minStack.empty() || minStack.top().second > x)
            minStack.push(newPair);
    }

    void pop() {
        if (stack.empty())
            return;
        if (stack.top().first == minStack.top().first)
            minStack.pop();
        stack.pop();
    }

    int top() {
        return stack.top().second;
    }

    int getMin() {
        return minStack.top().second;
    }
};

// int main() {
//     return 0;
// }
