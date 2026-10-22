//
// Created by Administrator on 2026/7/17.
//
/**
* 面试题 16.25. LRU 缓存
中等
相关标签
premium lock icon
相关企业
提示
设计和构建一个“最近最少使用”缓存，该缓存会删除最近最少使用的项目。缓存应该从键映射到值(允许你插入和检索特定键对应的值)，并在初始化时指定最大容量。当缓存被填满时，它应该删除最近最少使用的项目。

它应该支持以下操作： 获取数据 get 和 写入数据 put 。

获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。

示例：
 * @return
 */

#include <unordered_map>
#include <iostream>
#define MIN_CAPACITY 1

class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = std::max(capacity,MIN_CAPACITY);
        head = new DLinkedNode(0, 0);
        tail = new DLinkedNode(0, 0, head);
        head->next = tail;
        cache.reserve(this->capacity);
    }

    ~LRUCache() {
        while (head) {
            auto next = head->next;
            delete head;
            head = next;
        }
    }

    int get(int key) {
        auto pair = cache.find(key);
        if (pair == cache.end())
            return -1;
        //修改节点位置，放到head->next
        DLinkedNode *&cur = pair->second;
        updateNodeToHead(cur);
        return cur->value;
    }

    void put(int key, int value) {
        auto pair = cache.find(key);
        DLinkedNode *cur;
        if (pair != cache.end()) {
            (cur = pair->second)->value = value;
            //更新节点位置
            updateNodeToHead(cur);
        } else {
            cur = new DLinkedNode(key, value);
            //如果容量超过最大值，需要淘汰尾部
            if (cache.size() >= capacity)
                //淘汰尾部节点
                deleteTail();
            //添加
            cache.emplace(key, cur);
            insertHead(cur);
        }
    }

    struct DLinkedNode {
        int key, value;
        DLinkedNode *prev, *next;

        DLinkedNode(int key, int value, DLinkedNode *prev = nullptr, DLinkedNode *next = nullptr)
            : key(key),
              value(value),
              prev(prev),
              next(next) {
        }
    };

private:
    void deleteTail() {
        DLinkedNode *tl = tail->prev;
        deleteNode(tl);
        cache.erase(tl->key);
        delete tl;
    }

    void updateNodeToHead(DLinkedNode *&cur) {
        if (cur == head->next)
            return;
        deleteNode(cur);
        insertHead(cur);
    }

    void insertHead(DLinkedNode *&cur) {
        //断开head与head的后继,并同时与cur连接
        head->next->prev = cur;
        cur->next = head->next;
        head->next = cur;
        cur->prev = head;
    }

    DLinkedNode *&deleteNode(DLinkedNode *&cur) {
        //链接cur前驱与后继
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        cur->prev = nullptr;
        cur->next = nullptr;
        return cur;
    }

    int capacity;
    DLinkedNode *head, *tail;
    std::unordered_map<int, DLinkedNode *> cache;
};

// int main() {
//     /*LRUCache cache = new LRUCache( 2 );
//
//     // cache.put(1, 1);
//     // cache.put(2, 2);
//     // cache.get(1);       // 返回  1
//     // cache.put(3, 3);    // 该操作会使得密钥 2 作废
//     // cache.get(2);       // 返回 -1 (未找到)
//     // cache.put(4, 4);    // 该操作会使得密钥 1 作废
//     // cache.get(1);       // 返回 -1 (未找到)
//     // cache.get(3);       // 返回  3
//     // cache.get(4);       // 返回  4
//     */
//     LRUCache cache(2);
//     cache.put(1, 1);
//     cache.put(2, 2);
//     using namespace std;
//     cout << cache.get(1) << endl;
//     cache.put(3, 3);
//     cout << cache.get(2) << endl;
//     cache.put(4, 4);
//     cout << cache.get(1) << endl;
//     cout << cache.get(3) << endl;
//     cout << cache.get(4) << endl;
//
//     return 0;
// }
