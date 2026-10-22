//
// Created by Administrator on 2026/8/2.
//
/**
 *
 * @return
 */
#include <deque>
#include <vector>
using namespace std;
// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class NestedIterator {
    int index, dequeMaxSize;
    deque<int> nestDeque;
    vector<NestedInteger> *listPtr;

public:
    NestedIterator(vector<NestedInteger> &nestedList) : index(0), dequeMaxSize(1500), listPtr(&nestedList) {
    }

    int next() {
        const int value = nestDeque.front();
        nestDeque.pop_front();
        return value;
    }

    bool hasNext() {
        //如果index没有超过集合的size，说明还有值
        size_t listSize = listPtr->size();
        for (; nestDeque.size() < dequeMaxSize && index < listSize; index++) {
            addDequeNumber(&listPtr->at(index));
        }
        return !nestDeque.empty();
    }

private:
    void addDequeNumber(const NestedInteger *nit) {
        if (nit->isInteger()) {
            nestDeque.push_back(nit->getInteger());
        } else {
            auto &vt = nit->getList();
            const size_t size = vt.size();
            for (int i = 0; i < size; i++) {
                addDequeNumber(&vt[i]);
            }
        }
    }
};

// int main() {
//     return 0;
// }
