//
// Created by Administrator on 2026/6/25.
//
/**
* 725. 分隔链表
中等
相关标签
premium lock icon
相关企业
提示
给你一个头结点为 head 的单链表和一个整数 k ，请你设计一个算法将链表分隔为 k 个连续的部分。

每部分的长度应该尽可能的相等：任意两部分的长度差距不能超过 1 。这可能会导致有些部分为 null 。

这 k 个部分应该按照在链表中出现的顺序排列，并且排在前面的部分的长度应该大于或等于排在后面的长度。

返回一个由上述 k 部分组成的数组。


示例 1：


输入：head = [1,2,3], k = 5
输出：[[1],[2],[3],[],[]]
解释：
第一个元素 output[0] 为 output[0].val = 1 ，output[0].next = null 。
最后一个元素 output[4] 为 null ，但它作为 ListNode 的字符串表示是 [] 。
示例 2：


输入：head = [1,2,3,4,5,6,7,8,9,10], k = 3
输出：[[1,2,3,4],[5,6,7],[8,9,10]]
解释：
输入被分成了几个连续的部分，并且每部分的长度相差不超过 1 。前面部分的长度大于等于后面部分的长度。


提示：

链表中节点的数目在范围 [0, 1000]
0 <= Node.val <= 1000
1 <= k <= 50
 * @return
 */
#include <stdlib.h>

#include "../node/listnode.h"
typedef struct ListNode *list_ptr;

struct ListNode **splitListToParts(struct ListNode *head, int k, int *returnSize) {
    *returnSize = k;
    list_ptr *ret = calloc(k, sizeof(list_ptr));
    if (!head)
        return ret;
    list_ptr cur = head;
    int size = 0;
    while (cur) {
        size++;
        cur = cur->next;
    }
    //链表长度小于等于k，那就0~size-1各一个，size~k-1全部为null
    cur = head;
    int i = 0;
    if (size <= k) {
        for (; i < size; ++i) {
            ret[i] = cur;
            cur = cur->next;
            ret[i]->next = NULL;
        }
    }
    //size >k 时就需要去做除法，取余数，均摊余数
    else {
        //这是每个位置的基本元素个数
        int base_count = size / k;
        int remain = size % k;
        //余数为0，每个位置base_count个
        //余数不为0，那就从前面开始每个元素在截取base_count个之后，先判断remain是否归零，不归零再添加1个，同时remain--，直到remain归零
        for (; i < k; i++) {
            ret[i] = cur;
            int cur_count = 1;
            list_ptr end = cur;
            while (cur_count < base_count) {
                end = end->next;
                cur_count++;
            }
            //如果remain>0则再添加一个，并remain--
            if (remain) {
                end = end->next;
                remain--;
            }
            cur = end->next;
            end->next = NULL;
        }
    }
    return ret;
}

int main() {
    return 0;
}
