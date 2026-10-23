//
// Created by Administrator on 2026/7/9.
//
/**
* 2095. 删除链表的中间节点
中等
相关标签
premium lock icon
相关企业
提示
给你一个链表的头节点 head 。删除 链表的 中间节点 ，并返回修改后的链表的头节点 head 。

长度为 n 链表的中间节点是从头数起第 ⌊n / 2⌋ 个节点（下标从 0 开始），其中 ⌊x⌋ 表示小于或等于 x 的最大整数。

对于 n = 1、2、3、4 和 5 的情况，中间节点的下标分别是 0、1、1、2 和 2 。


示例 1：



输入：head = [1,3,4,7,1,2,6]
输出：[1,3,4,1,2,6]
解释：
上图表示给出的链表。节点的下标分别标注在每个节点的下方。
由于 n = 7 ，值为 7 的节点 3 是中间节点，用红色标注。
返回结果为移除节点后的新链表。
示例 2：



输入：head = [1,2,3,4]
输出：[1,2,4]
解释：
上图表示给出的链表。
对于 n = 4 ，值为 3 的节点 2 是中间节点，用红色标注。
示例 3：



输入：head = [2,1]
输出：[2]
解释：
上图表示给出的链表。
对于 n = 2 ，值为 1 的节点 1 是中间节点，用红色标注。
值为 2 的节点 0 是移除节点 1 后剩下的唯一一个节点。


提示：

链表中节点的数目在范围 [1, 105] 内
1 <= Node.val <= 105
 * @return
 */
#include "../link/ListNode.h"
#include <iostream>
using namespace std;

class Solution {
public:
    ListNode *deleteMiddle(ListNode *head) {
        if (!head->next) {
            delete head;
            return head;
        }
        if (!head->next->next) {
            delete head->next;
            head->next = nullptr;
            return head;
        }
        ListNode *slow = head, *fast = head->next->next;
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
            if (!fast->next)
                break;
            fast = fast->next;
        }
        //删除第slow的下一个节点
        ListNode *del = slow->next;
        slow->next = del->next;
        delete del;
        return head;
    }
};

// int main() {
//     ListNode *l5 = new ListNode(5);
//     ListNode *l4 = new ListNode(4, l5);
//     ListNode *l3 = new ListNode(3, l4);
//     ListNode *l2 = new ListNode(2, l3);
//     ListNode *l1 = new ListNode(1, l2);
//
//     Solution sl;
//     ListNode *list = sl.deleteMiddle(l1);
//     while (list) {
//         cout << (list->val) << endl;
//         ListNode *next = list->next;
//         delete list;
//         list = next;
//     }
//     return 0;
// }
