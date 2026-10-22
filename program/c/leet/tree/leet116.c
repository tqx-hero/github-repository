//
// Created by Administrator on 2026/6/13.
//

/**
* 116. 填充每个节点的下一个右侧节点指针
￼
中等
￼
相关标签
￼
相关企业
￼
给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。
初始状态下，所有 next 指针都被设置为 NULL。 
示例 1：
输入：
root = [1,2,3,4,5,6,7]
输出：
[1,#,2,3,#,4,5,6,7,#]
解释：
给定二叉树如图 A 所示，你的函数应该填充它的每个 next 指针，以指向其下一个右侧节点，如图 B 所示。序列化的输出按层序遍历排列，同一层节点由 next 指针连接，'#' 标志着每一层的结束。
示例 2:
输入：
root = []
输出：
[]
  提示：
• 树中节点的数量在 [0, 212 - 1] 范围内
• -1000 <= node.val <= 1000 
进阶：
• 你只能使用常量级额外空间。
• 使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。
 * @return
 */

#include <stdlib.h>

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

typedef struct Node Node;

void connect_sibling(Node *node) {
    if (!node || !node->left)
        return;
    node->left->next = node->right;
    if (node->next)
        node->right->next=node->next->left;
    connect_sibling(node->left);
    connect_sibling(node->right);
}

struct Node *connect(struct Node *root) {
    if (!root)
        return root;
    connect_sibling(root);
    return root;
}

int main() {
    // Node n7={7,NULL,NULL,NULL};
    // Node n6={6,NULL,NULL,NULL};
    // Node n5={5,NULL,NULL,NULL};
    // Node n4={4,NULL,NULL,NULL};
    // Node n3={3,&n6,&n7,NULL};
    // Node n2={2,&n4,&n5,NULL};
    // Node n1={1,&n2,&n3,NULL};

    Node n15={13,NULL,NULL,NULL};
    Node n14={12,NULL,NULL,NULL};
    Node n13={11,NULL,NULL,NULL};
    Node n12={10,NULL,NULL,NULL};
    Node n11={9,NULL,NULL,NULL};
    Node n10={8,NULL,NULL,NULL};
    Node n9={7,NULL,NULL,NULL};
    Node n8={6,NULL,NULL,NULL};
    Node n7={5,&n14,&n15,NULL};
    Node n6={4,&n12,&n13,NULL};
    Node n5={3,&n10,&n11,NULL};
    Node n4={2,&n8,&n9,NULL};
    Node n3={1,&n6,&n7,NULL};
    Node n2={0,&n4,&n5,NULL};
    Node n1={-1,&n2,&n3,NULL};
    Node * ret= connect(&n1);

    return 0;
}
