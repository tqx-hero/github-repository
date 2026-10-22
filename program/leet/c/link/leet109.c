//
// Created by Administrator on 2026/6/2.
//

/**
* 109. 有序链表转换二叉搜索树
￼
中等
￼
相关标签
￼
相关企业
￼
给定一个单链表的头节点  head ，其中的元素 按升序排序 ，将其转换为 平衡 二叉搜索树。 
示例 1:
￼
输入:
 head = [-10,-3,0,5,9]
输出:
 [0,-3,9,-10,null,5]
解释:
 一个可能的答案是[0，-3,9，-10,null,5]，它表示所示的高度平衡的二叉搜索树。
示例 2:
输入:
 head = []
输出:
 []
  提示:
• head 中的节点数在[0, 2 * 104] 范围内
• -105 <= Node.val <= 105
 * @return
 */
#include <stdio.h>
#include <stdlib.h>

#include "../node/listnode.h"
#include "../node/treenode.h"

//先遍历链表，将每个节点放到数组中，
//因为是升序排列，所以直接按顺序放即可
//放完以后每次选中间下标的节点作为根节点，从左半部分找左子树，右半部分找右子树
//左右子树仍然是找最中间的那个节点。
//就这样递归下去
#define TREENODE struct TreeNode*
#define LISTNODE struct ListNode*
typedef struct ListNode ListNode;
typedef struct TreeNode TreeNode;

//对数组内的元素，每次以中间元素作为根节点
TREENODE getBST(LISTNODE nodeArray[], int left, int right) {
    if (left > right)
        return NULL;
    int mid = left + (right - left) / 2;
    TREENODE node = malloc(sizeof(TreeNode));
    node->left = NULL;
    node->right = NULL;
    node->val = nodeArray[mid]->val;
    //拼接左子树
    node->left = getBST(nodeArray, left, mid - 1);
    //拼接右子树
    node->right = getBST(nodeArray, mid + 1, right);
    return node;
}

struct TreeNode *sortedListToBST(struct ListNode *head) {
    if (!head)
        return NULL;
    LISTNODE nodeArray[20001] = {NULL};
    //统计链表的节点数量
    int count = 0;
    LISTNODE cur = head;
    while (cur) {
        nodeArray[count++] = cur;
        cur = cur->next;
    }
    TREENODE bst = getBST(nodeArray, 0, count - 1);
    return bst;
}


// int main() {
//
//     struct ListNode l5 = {9, NULL};
//     struct ListNode l4 = {5, &l5};
//     struct ListNode l3 = {0, &l4};
//     struct ListNode l2 = {-3, &l3};
//     struct ListNode l1 = {-10, &l2};
//     TREENODE node = sortedListToBST(&l1);
//     TREENODE lptr = node;
//     // while (lptr) {
//     //     printf("%d ", lptr->val);
//     //     lptr = lptr->next;
//     // }
//     //注意：这里因为是leetcode题目，没有进行free内存操作导致了内存泄漏
//     //实际开发中使用完成需要释放内存
//     return 0;
// }
