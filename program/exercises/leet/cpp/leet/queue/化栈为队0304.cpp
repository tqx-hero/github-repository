//
// Created by Administrator on 2026/7/27.
//

#include <queue>
#include <stack>
/**
* 面试题 03.04. 化栈为队
简单
相关标签
premium lock icon
相关企业
提示
实现一个MyQueue类，该类用两个栈来实现一个队列。


示例：

MyQueue queue = new MyQueue();

queue.push(1);
queue.push(2);
queue.peek();  // 返回 1
queue.pop();   // 返回 1
queue.empty(); // 返回 false

说明：

你只能使用标准的栈操作 -- 也就是只有 push to top, peek/pop from top, size 和 is empty 操作是合法的。
你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。
假设所有操作都是有效的 （例如，一个空的队列不会调用 pop 或者 peek 操作）。
 */
class MyQueue {
    std::stack<int> inStack, outStack;

public:
    /** Initialize your data structure here. */
    MyQueue() {
    }

    /** Push element x to the back of queue. */
    void push(int x) {
        inStack.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        initOutStack();
        int val = outStack.top();
        outStack.pop();
        return val;
    }

    /** Get the front element. */
    int peek() {
        initOutStack();
        return outStack.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return outStack.empty() && inStack.empty();
    }

private:
    void initOutStack() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
    }
};

// int main() {
//     return 0;
// }
