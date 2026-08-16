//
// Created by Administrator on 2026/7/23.
//

/**
* LCR 031. LRU 缓存
中等
相关标签
premium lock icon
相关企业
运用所掌握的数据结构，设计和实现一个  LRU (Least Recently Used，最近最少使用) 缓存机制 。

实现 LRUCache 类：

LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。


示例：

输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4


提示：

1 <= capacity <= 3000
0 <= key <= 10000
0 <= value <= 105
最多调用 2 * 105 次 get 和 put


进阶：是否可以在 O(1) 时间复杂度内完成这两种操作？
 * @return
 */
#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) {
        cache.reserve(capacity);
    }

    int get(int key) {
        auto iter = cache.find(key);
        if (iter == cache.end())
            return -1;
        //存在需要将该值所在的迭代器放到链表头部
        leastCache.splice(leastCache.begin(), leastCache, iter->second);
        return iter->second->value;
    }

    void put(int key, int value) {
        auto iter = cache.find(key);
        //存在则修改其值
        if (iter != cache.end()) {
            iter->second->value = value;
            leastCache.splice(leastCache.begin(), leastCache, iter->second);
        } else {
            //容量超过了最大值，需要删除尾部
            if (cache.size() >= capacity) {
                cache.erase(leastCache.back().key);
                leastCache.pop_back();
            }
            auto it = leastCache.emplace(leastCache.begin(), key, value);
            cache.try_emplace(key, it);
        }
    }

private:
    struct myPair {
        int key;
        int value;

        myPair(int key, int value)
            : key(key),
              value(value) {
        }
    };

    int capacity;
    std::list<myPair> leastCache;
    std::unordered_map<int, std::list<myPair>::iterator> cache;
};
//
// int main() {
//     using namespace std;
//     /*LRUCache lRUCache = new LRUCache(2);
// lRUCache.put(1, 1); // 缓存是 {1=1}
// lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
// lRUCache.get(1);    // 返回 1
// lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
// lRUCache.get(2);    // 返回 -1 (未找到)
// lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
// lRUCache.get(1);    // 返回 -1 (未找到)
// lRUCache.get(3);    // 返回 3
// lRUCache.get(4);    // 返回 4*/
//     LRUCache lru(2);
//     lru.put(1, 1);
//     lru.put(2, 2);
//     cout << lru.get(1) << endl;
//     lru.put(3, 3);
//     cout << lru.get(2) << endl;
//     lru.put(4, 4);
//     cout << lru.get(1) << endl;
//     cout << lru.get(3) << endl;
//     cout << lru.get(4) << endl;
//     return 0;
// }
