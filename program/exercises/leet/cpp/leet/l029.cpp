//
// Created by Administrator on 2026/7/21.
//
/**
* LCR 029. 循环有序列表的插入
中等
相关标签
premium lock icon
相关企业
给定循环单调非递减列表中的一个点，写一个函数向这个列表中插入一个新元素 insertVal ，使这个列表仍然是循环升序的。

给定的可以是这个列表中任意一个顶点的指针，并不一定是这个列表中最小元素的指针。

如果有多个满足条件的插入位置，可以选择任意一个位置插入新的值，插入后整个列表仍然保持有序。

如果列表为空（给定的节点是 null），需要创建一个循环有序列表并返回这个节点。否则。请返回原先给定的节点。



示例 1：




输入：head = [3,4,1], insertVal = 2
输出：[3,4,1,2]
解释：在上图中，有一个包含三个元素的循环有序列表，你获得值为 3 的节点的指针，我们需要向表中插入元素 2 。新插入的节点应该在 1 和 3 之间，插入之后，整个列表如上图所示，最后返回节点 3 。


示例 2：

输入：head = [], insertVal = 1
输出：[1]
解释：列表为空（给定的节点是 null），创建一个循环有序列表并返回这个节点。
示例 3：

输入：head = [1], insertVal = 0
输出：[1,0]


提示：

0 <= Number of Nodes <= 5 * 10^4
-10^6 <= Node.val <= 10^6
-10^6 <= insertVal <= 10^6

 * @return
 */
#include <iostream>
#include <map>
using namespace std;

class Node {
public:
    int val;
    Node *next;

    Node() {
    }

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node *_next) {
        val = _val;
        next = _next;
    }
};


class Solution {
public:
    Node *insert(Node *head, int insertVal) {
        Node *newNode = new Node(insertVal);
        if (!head) {
            newNode->next = newNode;
            return newNode;
        }
        Node *cur = head;
        while (true) {
            int curVal = cur->val, nextVal = cur->next->val;
            //找到了相同的，直接插入到后面
            if (curVal == insertVal
                //如果当前值小于目标值：
                //1、next节点的值比当前值更小，说明没有更大的了，直接插入
                //2、next节点的值大于等于要插入的值，找到了需要插入的区间，直接插入
                || (curVal < insertVal &&
                    (nextVal < curVal || nextVal >= insertVal))
                ||
                //如果当前值大于目标值,需要找到更小的值：
                //1、若next小于当前值且大于等于目标值，说明该链表没有比目标值更小的了，直接插入
                //2、如果next小于当前值且小于目标值，说明该区间必然存在[v1,v2]，使得v1<=目标值<=v2,需要继续遍历
                (curVal > insertVal && nextVal < curVal && nextVal >= insertVal)
                ||
                //如果转一圈回来还没匹配到，那就直接插入
                cur->next == head
            ) {
                newNode->next = cur->next;
                cur->next = newNode;
                break;
            }
            cur = cur->next;
        }
        return head;
    }
};

// int main() {
//     Node *n3 = new Node(3);
//     Node *n2 = new Node(3, n3);
//     Node *n1 = new Node(3, n2);
//     n3->next = n1;
//     int val = 0;
//     Solution sl;
//     auto node = sl.insert(n1, val);
//     Node *cur = node;
//     int cnt = 0;
//     do {
//         cnt++;
//         cout << cur->val << " ";
//         cur = cur->next;
//     } while (cur != node) ;
//
//     for (int i = 0; i < cnt; i++) {
//         auto next = node->next;
//         delete node;
//         node = next;
//     }
//     return 0;
// }
