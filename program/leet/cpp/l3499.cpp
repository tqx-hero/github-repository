//
// Created by Administrator on 2026/7/21.
//

/**
* 3499. 操作后最大活跃区段数 I
中等
相关标签
premium lock icon
相关企业
提示
给你一个长度为 n 的二进制字符串 s，其中：

'1' 表示一个 活跃 区段。
'0' 表示一个 非活跃 区段。
你可以执行 最多一次操作 来最大化 s 中的活跃区段数量。在一次操作中，你可以：

将一个被 '0' 包围的连续 '1' 区块转换为全 '0'。
然后，将一个被 '1' 包围的连续 '0' 区块转换为全 '1'。
返回在执行最优操作后，s 中的 最大 活跃区段数。

注意：处理时需要在 s 的两侧加上 '1' ，即 t = '1' + s + '1'。这些加上的 '1' 不会影响最终的计数。



示例 1：

输入： s = "01"

输出： 1

解释：

因为没有被 '0' 包围的 '1' 区块，因此无法进行有效操作。最大活跃区段数为 1。

示例 2：

输入： s = "0100"

输出： 4

解释：

字符串 "0100" → 两端加上 '1' 后得到 "101001" 。
选择 "0100"，"101001" → "100001" → "111111" 。
最终的字符串去掉两端的 '1' 后为 "1111" 。最大活跃区段数为 4。
示例 3：

输入： s = "1000100"

输出： 7

解释：

字符串 "1000100" → 两端加上 '1' 后得到 "110001001" 。
选择 "000100"，"110001001" → "110000001" → "111111111"。
最终的字符串去掉两端的 '1' 后为 "1111111"。最大活跃区段数为 7。
示例 4：

输入： s = "01010"

输出： 4

解释：

字符串 "01010" → 两端加上 '1' 后得到 "1010101"。
选择 "010"，"1010101" → "1000101" → "1111101"。
最终的字符串去掉两端的 '1' 后为 "11110"。最大活跃区段数为 4。


提示：

1 <= n == s.length <= 105
s[i] 仅包含 '0' 或 '1'
 * @return
 */
#include <string>
#include <iostream>
#include <stack>
using namespace std;

class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int len = s.length();
        stack<int> stack;
        int count1 = 0, maxTotal = 0;
        bool left = false;
        for (int i = 0; i < len; i++) {
            char ch = s.at(i);
            if (stack.empty()) {
                //栈空且字符为0，入栈并开始统计
                if (ch == '0') {
                    left = true;
                    stack.push(i);
                } else
                    count1++;
                //如果是1，直接丢弃,因为左边不可能有0包裹它
            } else {
                char topCh = s.at(stack.top());
                //栈不为空
                if (ch == '0') {
                    //栈顶为0,直接丢弃
                    if (topCh == '0' && left)
                        continue;
                    //栈顶为1，表示正在统计
                    if (topCh == '0') {
                        do {
                            stack.pop();
                            topCh = s.at(stack.top());
                        } while (topCh == '0');
                    }
                    //当弹栈直到栈顶为1时，入栈
                    stack.push(i);
                } else {
                    count1++;
                    updateParams(topCh, s, stack, maxTotal, i, left);
                }
            }
        }
        //栈不为空，需要在统计剩余的区间
        if (!stack.empty())
            updateParams(s.at(stack.top()), s, stack, maxTotal, len, left);
        return count1 + maxTotal;
    }

private:
    void updateParams(char topCh, string &s, stack<int> &stack, int &maxTotal, int curOffset, bool &left) {
        //当字符为1时：
        if (topCh == '1') {
            stack.push(curOffset);
        } else {
            //栈顶=0且栈内还没有1，压栈并设置left标志位
            if (left) {
                stack.push(curOffset);
                left = false;
            } else {
                updateVariables(s, stack, maxTotal, curOffset);
                left = false;
            }
        }
    }

    void updateVariables(string &s, stack<int> &stack, int &maxTotal, int curOffset) {
        //栈顶为0且正在进行统计，此时需要将栈内元素全部统计，更新
        int curCount1 = 0, first1Offset = 0;
        do {
            stack.pop();
            char topCh = s.at(stack.top());
            if (topCh == '1') {
                if (!curCount1)
                    first1Offset = stack.top();
                curCount1++;
            }
        } while (stack.size() > 1);
        //获取栈底元素，即可获取这个区间内的长度
        maxTotal = max(maxTotal, curOffset - stack.top() - curCount1);
        //入栈第一个0位置与当前的1
        stack.pop();
        stack.push(first1Offset + 1);
        stack.push(curOffset);
    }
};

// int main() {
//     // string str = "10110";
//     // string str = "0111";
//     // string str = "0";
//     // string str = "01010";
//     // string str = "1000100";
//     // string str = "0100";
//     string str = "01";
//     cout << Solution().maxActiveSectionsAfterTrade(str) << endl;
//     return 0;
// }
