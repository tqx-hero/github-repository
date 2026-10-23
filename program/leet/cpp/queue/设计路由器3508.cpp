//
// Created by Administrator on 2026/7/29.
//

/**
 * 3508. 设计路由器
中等
相关标签
premium lock icon
相关企业
提示
请你设计一个数据结构来高效管理网络路由器中的数据包。每个数据包包含以下属性：

source：生成该数据包的机器的唯一标识符。
destination：目标机器的唯一标识符。
timestamp：该数据包到达路由器的时间戳。
实现 Router 类：

Router(int memoryLimit)：初始化路由器对象，并设置固定的内存限制。

memoryLimit 是路由器在任意时间点可以存储的 最大 数据包数量。
如果添加一个新数据包会超过这个限制，则必须移除 最旧的 数据包以腾出空间。
bool addPacket(int source, int destination, int timestamp)：将具有给定属性的数据包添加到路由器。

如果路由器中已经存在一个具有相同 source、destination 和 timestamp 的数据包，则视为重复数据包。
如果数据包成功添加（即不是重复数据包），返回 true；否则返回 false。
int[] forwardPacket()：以 FIFO（先进先出）顺序转发下一个数据包。

从存储中移除该数据包。
以数组 [source, destination, timestamp] 的形式返回该数据包。
如果没有数据包可以转发，则返回空数组。
int getCount(int destination, int startTime, int endTime)：

返回当前存储在路由器中（即尚未转发）的，且目标地址为指定 destination 且时间戳在范围 [startTime, endTime]（包括两端）内的数据包数量。
注意：对于 addPacket 的查询会按照 timestamp 的非递减顺序进行。



示例 1：

输入：
["Router", "addPacket", "addPacket", "addPacket", "addPacket", "addPacket", "forwardPacket", "addPacket", "getCount"]
[[3], [1, 4, 90], [2, 5, 90], [1, 4, 90], [3, 5, 95], [4, 5, 105], [], [5, 2, 110], [5, 100, 110]]

输出：
[null, true, true, false, true, true, [2, 5, 90], true, 1]

解释：

Router router = new Router(3); // 初始化路由器，内存限制为 3。
router.addPacket(1, 4, 90); // 数据包被添加，返回 True。
router.addPacket(2, 5, 90); // 数据包被添加，返回 True。
router.addPacket(1, 4, 90); // 这是一个重复数据包，返回 False。
router.addPacket(3, 5, 95); // 数据包被添加，返回 True。
router.addPacket(4, 5, 105); // 数据包被添加，[1, 4, 90] 被移除，因为数据包数量超过限制，返回 True。
router.forwardPacket(); // 转发数据包 [2, 5, 90] 并将其从路由器中移除。
router.addPacket(5, 2, 110); // 数据包被添加，返回 True。
router.getCount(5, 100, 110); // 唯一目标地址为 5 且时间在 [100, 110] 范围内的数据包是 [4, 5, 105]，返回 1。
示例 2：

输入：
["Router", "addPacket", "forwardPacket", "forwardPacket"]
[[2], [7, 4, 90], [], []]

输出：
[null, true, [7, 4, 90], []]

解释：

Router router = new Router(2); // 初始化路由器，内存限制为 2。
router.addPacket(7, 4, 90); // 返回 True。
router.forwardPacket(); // 返回 [7, 4, 90]。
router.forwardPacket(); // 没有数据包可以转发，返回 []。


提示：

2 <= memoryLimit <= 105
1 <= source, destination <= 2 * 105
1 <= timestamp <= 109
1 <= startTime <= endTime <= 109
addPacket、forwardPacket 和 getCount 方法的总调用次数最多为 105。
对于 addPacket 的查询，timestamp 按非递减顺序给出。
 * @return
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// class Router {
// public:
//     Router(int memoryLimit) : capacity(memoryLimit) {
//     }
//
//     bool addPacket(int source, int destination, int timestamp) {
//         //查看缓存中有无该数据包
//         //没有直接添加
//         shared_ptr<Node> ptr = make_shared<Node>(source, destination, timestamp);
//         if (cache.count(ptr))
//             return false;
//         if (packet_queue.size() >= capacity)
//             forwardPacket();
//         packet_queue.push(ptr);
//         cache.emplace(ptr);
//         auto map_iter = destCache.find(destination);
//         shared_ptr<DestCnt> destPtr = make_shared<DestCnt>(timestamp, 1);
//         if (map_iter != destCache.end()) {
//             auto &treeSet = map_iter->second;
//             auto set_iter = treeSet.find(destPtr);
//             //如果存在时间戳那项，则直接增加计数
//             if (set_iter != treeSet.end())
//                 (*set_iter)->cnt++;
//             else
//                 //不存在则添加这一项
//                 treeSet.emplace(destPtr);
//         } else
//         //如果不存在该项，添加
//             destCache[destination].emplace(destPtr);
//         return true;
//     }
//
//     vector<int> forwardPacket() {
//         vector<int> vc;
//         if (!packet_queue.empty()) {
//             //不为空，需要弹出队列头部，并且删除缓存中的那项数据
//             shared_ptr<Node> ptr = packet_queue.front();
//             int key = ptr->dest, time = ptr->timeStamp;
//             vc = {ptr->src, key, time};
//             //找到目的地址相关的时间戳集合
//             auto map_iter = destCache.find(key);
//             if (map_iter != destCache.end()) {
//                 auto &treeSet = map_iter->second;
//                 auto set_iter = treeSet.find(make_shared<DestCnt>(time, 0));
//                 //如果存在，需要使cnt-1
//                 if (set_iter != treeSet.end()) {
//                     int cnt = (*set_iter)->cnt--;
//                     if (cnt == 1)
//                         treeSet.erase(set_iter);
//                     if (treeSet.empty())
//                         destCache.erase(map_iter);
//                 }
//             }
//             packet_queue.pop();
//             auto iter_set = cache.find(ptr);
//             if (iter_set == cache.end())
//                 return vc;
//             cache.erase(iter_set);
//         }
//         return vc;
//     }
//
//     int getCount(int destination, int startTime, int endTime) {
//         auto mapIter = destCache.find(destination);
//         if (mapIter == destCache.end())
//             return 0;
//         auto &list = mapIter->second;
//         auto lower = list.lower_bound(make_shared<DestCnt>(startTime, 0));
//         auto higher = list.upper_bound(make_shared<DestCnt>(endTime, 0));
//         if (lower == higher)
//             return 0;
//         while ((*--higher)->timeStamp > endTime);
//         int cnt = (*lower)->cnt;
//         for (; higher != lower; --higher) {
//             cnt += (*higher)->cnt;
//         }
//         return cnt;
//     }
//
// private:
//     struct Node {
//         int src, dest, timeStamp;
//
//         Node(int src, int dest, int time_stamp)
//             : src(src),
//               dest(dest),
//               timeStamp(time_stamp) {
//         }
//
//         bool operator==(const Node &other) const {
//             return src == other.src && dest == other.dest && timeStamp == other.timeStamp;
//         }
//     };
//
//     struct NodeHash {
//         // 通用哈希合并函数（C++11 可用）
//         template<typename T>
//         void hash_combine(size_t &seed, const T &val) const noexcept {
//             std::hash<T> hasher;
//             seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//         }
//
//         size_t operator()(const shared_ptr<Node> &n) const noexcept {
//             size_t seed = 0;
//             hash_combine(seed, n->src);
//             hash_combine(seed, n->dest);
//             hash_combine(seed, n->timeStamp);
//             return seed;
//         }
//     };
//
//     struct NodeEquals {
//         bool operator()(const shared_ptr<Node> &x, const shared_ptr<Node> &y) const {
//             return *x == *y;
//         }
//     };
//
//     ///////////////////////定义放入哈希表中的树的排序以及比较规则
//     struct DestCnt {
//         int timeStamp, cnt;
//
//         DestCnt(int time_stamp, int cnt)
//             : timeStamp(time_stamp),
//               cnt(cnt) {
//         }
//
//         bool operator==(const DestCnt &ann) const {
//             return timeStamp == ann.timeStamp;
//         }
//     };
//
//     struct CmpDestCnt {
//         bool operator()(const shared_ptr<DestCnt> &p1, const shared_ptr<DestCnt> &p2) const {
//             return p1->timeStamp < p2->timeStamp;
//         }
//     };
//
//     int capacity;
//     //todo 大数据量下还是会超时，需要在设置一个哈希表用来存储按照dest存放不同时间戳不同的数量，扁平化查询count \
//     存放每个节点的缓存需要把map换成set
//     unordered_set<shared_ptr<Node>, NodeHash, NodeEquals> cache;
//     unordered_map<int, set<shared_ptr<DestCnt>, CmpDestCnt> > destCache;
//     queue<shared_ptr<Node> > packet_queue;
// };


class Router {
public:
    int memLimit = 0;
    int length = 0;
    set<tuple<int, int, int>> isExist;
    unordered_map<int, deque<int>> sameDestQue;
    deque<tuple<int, int, int>> que;

    Router(int memoryLimit) { memLimit = memoryLimit; }

    bool addPacket(int source, int destination, int timestamp) {
        tuple<int, int, int> packet =
            make_tuple(source, destination, timestamp);
        if (isExist.count(packet)) {
            return false;
        }
        if (length == memLimit) {
            forwardPacket();
        }
        length++;
        que.push_back(packet);
        sameDestQue[destination].push_back(timestamp);
        isExist.insert(packet);
        return true;
    }

    vector<int> forwardPacket() {
        vector<int> data;
        if (!que.empty()) {
            tuple<int, int, int> packet = que.front();
            que.pop_front();
            data = vector<int>{get<0>(packet), get<1>(packet), get<2>(packet)};
            isExist.erase(packet);
            sameDestQue[data[1]].pop_front();
            length--;
        }
        return data;
    }

    int getCount(int destination, int startTime, int endTime) {
        auto pos1 = lower_bound(sameDestQue[destination].begin(),
                                sameDestQue[destination].end(), startTime);
        auto pos2 = upper_bound(sameDestQue[destination].begin(),
                                sameDestQue[destination].end(), endTime);
        return pos2 - pos1;
    }
};
// int main() {
//     /*["Router", "addPacket",   "forwardPacket", "forwardPacket"]
// [       [2],        [7, 4, 90],         [],         []]
// [       null,       true,           [7, 4, 90],         []]*/
//     // Router rt(2);
//     // cout << rt.addPacket(7, 4, 90) << endl;
//     // const auto &packet = rt.forwardPacket();
//     // std::for_each(packet.begin(), packet.end(), print);
//     // const auto &packet2 = rt.forwardPacket();
//     // std::for_each(packet2.begin(), packet2.end(), print);
//
//     /*["Router", "addPacket", "addPacket", "addPacket", "addPacket", "addPacket", "forwardPacket", "addPacket", "getCount"]
// [       [3],      [1, 4, 90],  [2, 5, 90], [1, 4, 90],   [3, 5, 95], [4, 5, 105],       [],         [5, 2, 110], [5, 100, 110]]
// 输出：
// [null, true, true, false, true, true, [2, 5, 90], true, 1]*/
//     // Router rt{3};
//     // cout << rt.addPacket(1, 4, 90) << endl;
//     // cout << rt.addPacket(2, 5, 90) << endl;
//     // cout << rt.addPacket(1, 4, 90) << endl;
//     // cout << rt.addPacket(3, 5, 95) << endl;
//     // cout << rt.addPacket(4, 5, 105) << endl;
//     // const auto &packet2 = rt.forwardPacket();
//     // std::for_each(packet2.begin(), packet2.end(), [](const int &a) { cout << a << endl; });
//     // cout << rt.addPacket(5, 2, 110) << endl;
//     // cout << rt.getCount(5, 100, 110) << endl;
//
//     /*["Router","addPacket","addPacket","addPacket","getCount"]
// ￼
//         [[2],       [4,3,1],    [5,4,1],    [2,3,4],    [4,1,3]]*/
//     Router rt(2);
//     cout << rt.addPacket(4, 3, 1) << endl;
//     cout << rt.addPacket(5, 4, 1) << endl;
//     cout << rt.addPacket(2, 3, 4) << endl;
//     cout << rt.getCount(4, 1, 3) << endl;
//
//     return 0;
// }
