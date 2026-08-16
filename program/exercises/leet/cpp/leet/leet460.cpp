//
// Created by Administrator on 2026/7/14.
//
/**
* 460. LFU 缓存
困难
相关标签
premium lock icon
相关企业
请你为 最不经常使用（LFU）缓存算法设计并实现数据结构。

实现 LFUCache 类：

LFUCache(int capacity) - 用数据结构的容量 capacity 初始化对象
int get(int key) - 如果键 key 存在于缓存中，则获取键的值，否则返回 -1 。
void put(int key, int value) - 如果键 key 已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量 capacity 时，则应该在插入新项之前，移除最不经常使用的项。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除 最久未使用 的键。
为了确定最不常使用的键，可以为缓存中的每个键维护一个 使用计数器 。使用计数最小的键是最久未使用的键。

当一个键首次插入到缓存中时，它的使用计数器被设置为 1 (由于 put 操作)。对缓存中的键执行 get 或 put 操作，使用计数器的值将会递增。

函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。



示例：

输入：
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
输出：
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

解释：
// cnt(x) = 键 x 的使用计数
// cache=[] 将显示最后一次使用的顺序（最左边的元素是最近的）
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // 返回 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 去除键 2 ，因为 cnt(2)=1 ，使用计数最小
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // 返回 -1（未找到）
lfu.get(3);      // 返回 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // 去除键 1 ，1 和 3 的 cnt 相同，但 1 最久未使用
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // 返回 -1（未找到）
lfu.get(3);      // 返回 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // 返回 4
                 // cache=[3,4], cnt(4)=2, cnt(3)=3


提示：

1 <= capacity <= 104
0 <= key <= 105
0 <= value <= 109
最多调用 2 * 105 次 get 和 put 方法
 * @return
 */
#include <iostream>
#include <unordered_map>
#define MAX_BUCKETS_CAPACITY 200001
using namespace std;

class LFUDLinkNode {
public:
    int key, value, count;
    LFUDLinkNode *prev, *next;

    LFUDLinkNode(int key, int value) : key(key), value(value), count(1),
                                       prev(nullptr), next(nullptr) {
    }

    LFUDLinkNode(int key, int value, int count, LFUDLinkNode *prev = nullptr,
                 LFUDLinkNode *next = nullptr)
        : key(key),
          value(value),
          count(count),
          prev(prev),
          next(next) {
    }
};

class LinkedList {
public:
    int size;
    LFUDLinkNode *head, *tail;

    LinkedList() : size(0) {
        head = new LFUDLinkNode(0, 0, 0);
        tail = new LFUDLinkNode(0, 0, 0, head);
        head->next = tail;
    }

    LFUDLinkNode *&deleteNode(LFUDLinkNode *&cur) {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        cur->prev = nullptr;
        cur->next = nullptr;
        this->size--;
        return cur;
    }

    //头插法
    void addHead(LFUDLinkNode *&cur) {
        cur->next = head->next;
        head->next->prev = cur;
        cur->prev = head;
        head->next = cur;
        this->size++;
    }

    LFUDLinkNode *deleteTail() {
        LFUDLinkNode *prev = tail->prev;
        prev->prev->next = tail;
        tail->prev = prev->prev;
        prev->next = nullptr;
        prev->next = nullptr;
        this->size--;
        return prev;
    }

    ~LinkedList() {
        while (head) {
            auto next = head->next;
            head->prev = nullptr;
            head->next = nullptr;
            delete head;
            head = next;
        }
    }
};

class LFUCache {
public:
    LFUCache(int capacity) : capacity(capacity) {
        cache.reserve(capacity);
        deletedIndex = 0;
        this->buckets.reserve(MAX_BUCKETS_CAPACITY);
        for (int i = 0; i < MAX_BUCKETS_CAPACITY; i++) {
            LinkedList *t = new LinkedList;
            this->buckets.push_back(t);
        }
    }

    int get(int key) {
        if (auto ptr = get_key_entry(key)) {
            //更新ptr的位置
            updateNodePosition(ptr);
            return ptr->value;
        }
        return -1;
    }

    void put(int key, int value) {
        LFUDLinkNode *ptr;
        if (!(ptr = get_key_entry(key))) {
            //不存在，首先应该判断size是否已经达到最大容量，未达到直接添加，达到需要淘汰
            insertNode(new LFUDLinkNode(key, value, 1));
        } else {
            ptr->value = value;
            updateNodePosition(ptr);
        }
    }

    ~LFUCache() {
        for (int i = 0; i < MAX_BUCKETS_CAPACITY; i++) {
            delete buckets.at(i);
        }
    }

private:
    void insertNode(LFUDLinkNode *ptr) {
        if (cache.size() >= capacity)
            //删除尾节点
            deleteTail();
        deletedIndex = 1;
        buckets.at(deletedIndex)->addHead(ptr);
        cache.emplace(ptr->key, ptr);
    }

    LFUDLinkNode *get_key_entry(int key) {
        auto iter = cache.find(key);
        if (iter == cache.end())
            return nullptr;
        return iter->second;
    }

    void deleteTail() {
        LFUDLinkNode *delete_tail = buckets.at(deletedIndex)->deleteTail();
        cache.erase(delete_tail->key);
        delete delete_tail;
    }

    void updateNodePosition(LFUDLinkNode *ptr) {
        int bucketIndex = ptr->count;
        LinkedList *&bucket = buckets.at(bucketIndex);
        bucket->deleteNode(ptr);
        ptr->count++;
        buckets.at(bucketIndex + 1)->addHead(ptr);
        if (bucket->size == 0 && deletedIndex == bucketIndex)
            deletedIndex++;
    }

    int capacity, deletedIndex;
    unordered_map<int, LFUDLinkNode *> cache;
    vector<LinkedList *> buckets;
};

// int main() {
//     LFUCache *lfu = new LFUCache(2);
//     /*
// lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
// lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
// lfu.get(1);      // 返回 1
//                  // cache=[1,2], cnt(2)=1, cnt(1)=2
// lfu.put(3, 3);   // 去除键 2 ，因为 cnt(2)=1 ，使用计数最小
//                  // cache=[3,1], cnt(3)=1, cnt(1)=2
// lfu.get(2);      // 返回 -1（未找到）
// lfu.get(3);      // 返回 3
//                  // cache=[3,1], cnt(3)=2, cnt(1)=2
// lfu.put(4, 4);   // 去除键 1 ，1 和 3 的 cnt 相同，但 1 最久未使用
//                  // cache=[4,3], cnt(4)=1, cnt(3)=2
// lfu.get(1);      // 返回 -1（未找到）
// lfu.get(3);      // 返回 3
//                  // cache=[3,4], cnt(4)=1, cnt(3)=3
// lfu.get(4);      // 返回 4
//                  // cache=[3,4], cnt(4)=2, cnt(3)=3*/
//     lfu->put(1, 1);
//     lfu->put(2, 2);
//     cout << lfu->get(1) << endl;
//     lfu->put(3, 3);
//     cout << lfu->get(2) << endl;
//     cout << lfu->get(3) << endl;
//     lfu->put(4, 4);
//     cout << lfu->get(1) << endl;
//     cout << lfu->get(3) << endl;
//     cout << lfu->get(4) << endl;
//
//     /*["LFUCache","put","put","put","put","get"]
// ￼
// [[2],[3,1],[2,1],[2,2],[4,4],[2]]*/
//
//     // lfu->put(3, 1);
//     // lfu->put(2, 1);
//     // lfu->put(2, 2);
//     // lfu->put(4, 4);
//     // cout << lfu->get(2) << endl;
//     delete lfu;
//     return 0;
// }
