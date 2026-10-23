//
// Created by Administrator on 2026/8/1.
//
/**
* 面试题 03.05. 栈排序
中等
相关标签
premium lock icon
相关企业
提示
栈排序。 编写程序，对栈进行排序使最小元素位于栈顶。最多只能使用一个其他的临时栈存放数据，但不得将元素复制到别的数据结构（如数组）中。该栈支持如下操作：push、pop、peek 和 isEmpty。当栈为空时，peek 返回 -1。

示例 1：

 输入：
["SortedStack", "push", "push", "peek", "pop", "peek"]
[[], [1], [2], [], [], []]
 输出：
[null,null,null,1,null,2]
示例 2：

 输入：
["SortedStack", "pop", "pop", "push", "pop", "isEmpty"]
[[], [], [], [1], [], []]
 输出：
[null,null,null,null,null,true]
提示：

栈中的元素数目在[0, 5000]范围内。
 * @return
 */
#include <iostream>
#include <stack>
using namespace std;

class SortedStack {
    stack<int> valStack;

public:
    SortedStack() {
    }

    void push(int val) {
        if (valStack.empty() || valStack.top() >= val) {
            valStack.push(val);
            return;
        }
        stack<int> tempStack;
        int num;
        while (!valStack.empty() && (num = valStack.top()) < val) {
            tempStack.push(num);
            valStack.pop();
        }
        valStack.push(val);
        while (!tempStack.empty()) {
            valStack.push(tempStack.top());
            tempStack.pop();
        }
    }

    void pop() {
        if (!valStack.empty())
            valStack.pop();
    }

    int peek() {
        if (valStack.empty())
            return -1;
        return valStack.top();
    }

    bool isEmpty() {
        return valStack.empty();
    }
};

// int main() {
//     /*["SortedStack", "push", "push", "peek", "pop", "peek"]
// [           [],         [1],    [2],    [],     [],     []]
//  输出
// ：
// [           null,       null,   null,    1,     null,   2]*/
//     SortedStack st;
//     st.push(1);
//     st.push(2);
//     cout << st.peek() << endl;
//     st.pop();
//     cout << st.peek() << endl;
//     return 0;
// }
