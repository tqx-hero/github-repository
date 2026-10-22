//
// Created by Administrator on 2026/8/2.
//
/**
* 2327. 知道秘密的人数
中等
相关标签
premium lock icon
相关企业
提示
在第 1 天，有一个人发现了一个秘密。

给你一个整数 delay ，表示每个人会在发现秘密后的 delay 天之后，每天 给一个新的人 分享 秘密。同时给你一个整数 forget ，表示每个人在发现秘密 forget 天之后会 忘记 这个秘密。一个人 不能 在忘记秘密那一天及之后的日子里分享秘密。

给你一个整数 n ，请你返回在第 n 天结束时，知道秘密的人数。由于答案可能会很大，请你将结果对 109 + 7 取余 后返回。



示例 1：

输入：n = 6, delay = 2, forget = 4
输出：5
解释：
第 1 天：假设第一个人叫 A 。（一个人知道秘密）
第 2 天：A 是唯一一个知道秘密的人。（一个人知道秘密）
第 3 天：A 把秘密分享给 B 。（两个人知道秘密）
第 4 天：A 把秘密分享给一个新的人 C 。（三个人知道秘密）
第 5 天：A 忘记了秘密，B 把秘密分享给一个新的人 D 。（三个人知道秘密）
第 6 天：B 把秘密分享给 E，C 把秘密分享给 F 。（五个人知道秘密）
示例 2：

输入：n = 4, delay = 1, forget = 3
输出：6
解释：
第 1 天：第一个知道秘密的人为 A 。（一个人知道秘密）
第 2 天：A 把秘密分享给 B 。（两个人知道秘密）
第 3 天：A 和 B 把秘密分享给 2 个新的人 C 和 D 。（四个人知道秘密）
第 4 天：A 忘记了秘密，B、C、D 分别分享给 3 个新的人。（六个人知道秘密）


提示：

2 <= n <= 1000
1 <= delay < forget <= n
 * @return
 */
#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        //定义一个队列，存放知道秘密的人,数对为:[第几天开始传播给下一个人,第几天忘掉并停止]
        deque<pair<int, int> > peopleQueue;
        long long cnt = 0;
        int mod = 1000000007;
        peopleQueue.emplace_back(1 + delay, 1 + forget);
        int i;
        while (!peopleQueue.empty()) {
            size_t size = peopleQueue.size();
            for (i = 0; i < size; i++) {
                pair<int, int> pair = peopleQueue.front();
                peopleQueue.pop_front();
                //如果忘掉的那天大于统计的那天n，表示这个人还记得秘密，计数+1
                if (pair.second > n)
                    cnt++;
                int limit = min(pair.second, n + 1);
                for (int j = pair.first; j < limit; j++) {
                    //如果传播的下一个人到他开始传播的那天超过统计天数，说明这个人到统计那天为止不会再次传播，直接排除不入队
                    if (j + delay > n) {
                        cnt++;
                        continue;
                    }
                    peopleQueue.emplace_back(j + delay, j + forget);
                }
            }
        }
        return static_cast<int>(cnt % mod);
    }
};

// int main() {
//     int n = 4, delay = 1, forget = 3;
//     // int n = 6, delay = 2, forget = 4;
//     Solution sl;
//     cout << sl.peopleAwareOfSecret(n, delay, forget) << endl;
//     return 0;
// }
