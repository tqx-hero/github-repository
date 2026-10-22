//
// Created by Administrator on 2026/7/2.
//
/**
* 1721. 交换链表中的节点
中等
相关标签
premium lock icon
相关企业
提示
给你链表的头节点 head 和一个整数 k 。

交换 链表正数第 k 个节点和倒数第 k 个节点的值后，返回链表的头节点（链表 从 1 开始索引）。



示例 1：


输入：head = [1,2,3,4,5], k = 2
输出：[1,4,3,2,5]
示例 2：

输入：head = [7,9,6,6,7,8,3,0,9,5], k = 5
输出：[7,9,6,6,8,7,3,0,9,5]
示例 3：

输入：head = [1], k = 1
输出：[1]
示例 4：

输入：head = [1,2], k = 1
输出：[2,1]
示例 5：

输入：head = [1,2,3], k = 2
输出：[1,2,3]


提示：

链表中节点的数目是 n
1 <= k <= n <= 105
0 <= Node.val <= 100
 * @return
 */
#include <stdlib.h>
#include <time.h>

#include "../node/listnode.h"
typedef struct ListNode *list_ptr;
//快慢指针
//快指针到头后统计出了链表的长度
//慢指针一步步往前移，当快指针到头统计出长度时，这时看一下慢指针有没有到k，或者有没有到len-k+1
//最终结果就是统计这两个节点的值，然后交换即可
//最好的情况是k比较小，在快指针到头前统计好了k的指针
//然后有了长度以后在统计len-k+1,一次慢指针遍历即可达到
//最坏的情况是k>len/2，快指针到头了k还没到，但是len-k+1已经过了，这时还需要再次从1到len-k+1找到那个节点
struct ListNode *swapNodes(struct ListNode *head, int k) {
    if (!head->next)
        return head;
    int len = 0;
    list_ptr cur = head, k_ptr = NULL, r_k_ptr = NULL;
    //第一遍遍历找到第k个节点，统计长度
    while (cur) {
        len++;
        if (k == len)
            k_ptr = cur;
        cur = cur->next;
    }
    int r_k = len - k + 1, i = 0;
    cur = head;
    while (cur) {
        i++;
        if (i == r_k) {
            r_k_ptr = cur;
            break;
        }
        cur = cur->next;
    }
    if (k_ptr && r_k_ptr) {
        int tmp = k_ptr->val;
        k_ptr->val = r_k_ptr->val;
        r_k_ptr->val = tmp;
    }
    return head;
}

int main() {
    return 0;
}
