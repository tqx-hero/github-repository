//
// Created by Administrator on 2026/8/6.
//
/**
* 946. 验证栈序列
中等
相关标签
premium lock icon
相关企业
给定 pushed 和 popped 两个序列，每个序列中的 值都不重复，只有当它们可能是在最初空栈上进行的推入 push 和弹出 pop 操作序列的结果时，返回 true；否则，返回 false 。



示例 1：

输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
输出：true
解释：我们可以按以下顺序执行：
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
示例 2：

输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
输出：false
解释：1 不能在 2 之前弹出。


提示：

1 <= pushed.length <= 1000
0 <= pushed[i] <= 1000
pushed 的所有元素 互不相同
popped.length == pushed.length
popped 是 pushed 的一个排列
 * @return
 */
#include <iostream>
#include <unordered_set>
#include <vector>
#include <stack>
using namespace std;

class Solution {
    bool dealStack(stack<int> &numStack, int &i, vector<int> &popped, int num, unordered_set<int> &cache) {
        int cur = popped[i];
        if (num == cur)
            i++;
        else {
            //如果还没放到栈中，数字入栈，并且入cache
            if (!cache.count(cur)) {
                cache.emplace(num);
                numStack.push(num);
            } else if (numStack.top() != cur)
                return false;
            else {
                //栈中已经存在且栈顶等于cur
                numStack.pop();
                i++;
                return dealStack(numStack, i, popped, num, cache);
            }
        }
        return true;
    }

public:
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped) {
        unordered_set<int> cache;
        stack<int> numStack;
        int i = 0, size = static_cast<int>(popped.size());
        for (auto num: pushed) {
            if (!dealStack(numStack, i, popped, num, cache))
                return false;
        }
        for (; i < size; i++) {
            if (numStack.top() != popped[i])
                return false;
            numStack.pop();
        }
        return true;
    }
};

// int main() {
//     // vector<int> pushed = {1, 2, 3, 4, 5}, popped = {4, 3, 5, 1, 2};
//     vector<int> pushed = {1, 2, 3, 4, 5}, popped = {4, 5, 3, 2, 1};
//     Solution sl;
//     cout << sl.validateStackSequences(pushed, popped) << endl;
//     return 0;
// }
