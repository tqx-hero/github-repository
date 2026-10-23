//
// Created by Administrator on 2026/7/30.
//
/**
* LCR 184. 设计自助结算系统
中等
相关标签
premium lock icon
相关企业
请设计一个自助结账系统，该系统需要通过一个队列来模拟顾客通过购物车的结算过程，需要实现的功能有：

get_max()：获取结算商品中的最高价格，如果队列为空，则返回 -1
add(value)：将价格为 value 的商品加入待结算商品队列的尾部
remove()：移除第一个待结算的商品价格，如果队列为空，则返回 -1
注意，为保证该系统运转高效性，以上函数的均摊时间复杂度均为 O(1)



示例 1：

输入:
["Checkout","add","add","get_max","remove","get_max"]
[[],[4],[7],[],[],[]]

输出: [null,null,null,7,4,7]
示例 2：

输入:
["Checkout","remove","get_max"]
[[],[],[]]

输出: [null,-1,-1]


提示：

1 <= get_max, add, remove 的总操作数 <= 10000
1 <= value <= 10^5
 * @return
 */

#include <iostream>
#include <queue>

class Checkout {
    int index;
    std::queue<std::pair<int, int> > checkQueue;
    std::deque<std::pair<int, int> > maxQueue;

public:
    Checkout() : index(0) {
    }

    int get_max() {
        if (checkQueue.empty())
            return -1;
        return maxQueue.front().second;
    }

    void add(int value) {
        std::pair<int, int> pair = std::make_pair(index++, value);
        checkQueue.push(pair);
        while (!maxQueue.empty() && maxQueue.back().second <= value)
            maxQueue.pop_back();
        maxQueue.push_back(pair);
    }

    int remove() {
        if (checkQueue.empty())
            return -1;
        std::pair<int, int> &pair = checkQueue.front();
        if (maxQueue.front().first == pair.first)
            maxQueue.pop_front();
        int ret = pair.second;
        checkQueue.pop();
        return ret;
    }
};

// int main() {
//     /*["Checkout","add","add","get_max","remove","get_max"]
// [           [],     [4],  [7],  [],         [],     []]
//
// 输出:         [null,null, null,   7,          4,  7]*/
//     using namespace std;
//     Checkout ck;
//     ck.add(4);
//     ck.add(7);
//     cout << ck.get_max() << endl;
//     cout << ck.remove() << endl;
//     cout << ck.get_max() << endl;
//     return 0;
// }
