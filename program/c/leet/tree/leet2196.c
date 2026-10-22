//
// Created by Administrator on 2026/6/7.
//

/**
* 2196. 根据描述创建二叉树
中等
相关标签
premium lock icon
相关企业
提示
给你一个二维整数数组 descriptions ，其中 descriptions[i] = [parenti, childi, isLefti] 表示 parenti 是 childi 在 二叉树 中的 父节点，二叉树中各节点的值 互不相同 。此外：

如果 isLefti == 1 ，那么 childi 就是 parenti 的左子节点。
如果 isLefti == 0 ，那么 childi 就是 parenti 的右子节点。
请你根据 descriptions 的描述来构造二叉树并返回其 根节点 。

测试用例会保证可以构造出 有效 的二叉树。



示例 1：



输入：descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
输出：[50,20,80,15,17,19]
解释：根节点是值为 50 的节点，因为它没有父节点。
结果二叉树如上图所示。
示例 2：



输入：descriptions = [[1,2,1],[2,3,0],[3,4,1]]
输出：[1,2,null,null,3,4]
解释：根节点是值为 1 的节点，因为它没有父节点。
结果二叉树如上图所示。


提示：

1 <= descriptions.length <= 104
descriptions[i].length == 3
1 <= parenti, childi <= 105
0 <= isLefti <= 1
descriptions 所描述的二叉树是一棵有效二叉树
 * @return
 */
#include <stdlib.h>

#include "../node/treenode.h"
#define HASH_SIZE 1009   // 质数，减少冲突

#define TREENODE struct TreeNode*
#define VOID void*
#define HASHNODE HashNode*
// #define HASHTABLE(table) HASHNODE table
typedef struct TreeNode TreeNode;


// 哈希结点
typedef struct HashNode {
    int key;
    VOID val;
    struct HashNode *next;
} HashNode;

// HashNode *hashTable[HASH_SIZE];

// 哈希映射函数
static int hashFunc(int key) {
    return abs(key) % HASH_SIZE;
}

// 初始化哈希表
void hashInit(HASHNODE *hash) {
    for (int i = 0; i < HASH_SIZE; i++)
        hash[i] = NULL;
}

// 插入/更新
void hashPut(HASHNODE *hash, int key, VOID val) {
    int idx = hashFunc(key);
    HashNode *cur = hash[idx];
    // 存在则更新
    while (cur) {
        if (cur->key == key) {
            cur->val = val;
            return;
        }
        cur = cur->next;
    }
    // 头插新建结点
    HashNode *newNode = (HashNode *) malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->val = val;
    newNode->next = hash[idx];
    hash[idx] = newNode;
}

// 查找，不存在返回NULL
VOID hashGet(HASHNODE *hash, int key) {
    int idx = hashFunc(key);
    HashNode *cur = hash[idx];
    while (cur) {
        if (cur->key == key)
            return cur->val;
        cur = cur->next;
    }
    return NULL;
}

// 删除键
void hashRemove(HASHNODE *hash, int key) {
    int idx = hashFunc(key);
    HashNode **p = &hash[idx];
    while (*p) {
        if ((*p)->key == key) {
            HashNode *del = *p;
            *p = (*p)->next;
            free(del);
            return;
        }
        p = &(*p)->next;
    }
}

// 释放整张哈希表
void hashFree(HASHNODE *hash) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *cur = hash[i];
        while (cur) {
            HashNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}

struct TreeNode *createBinaryTree(int **descriptions, int descriptionsSize, int *descriptionsColSize) {
    //nodeHash放入节点
    //hashParent判断有无父节点：1、无父结点；2、有父节点
    HASHNODE nodeHash[HASH_SIZE];
    HASHNODE hashParent[HASH_SIZE];
    hashInit(nodeHash);
    hashInit(hashParent);
    int i = 0;
    //descriptionsSize是二维数组的长度[1,10^4]
    //descriptionsColSize是一维数组的元素个数，固定为3
    for (; i < descriptionsSize; ++i) {
        int *description = descriptions[i];
        //获取子树状态：1、左子树；0、右子树
        int getState = description[2];
        int parent = description[0];
        int child = description[1];
        TREENODE childNode = NULL;
        TREENODE parentNode = NULL;
        //拿到父子节点
        if (!(childNode = hashGet(nodeHash, child))) {
            childNode = malloc(sizeof(TreeNode));
            childNode->left=NULL;
            childNode->right=NULL;
            childNode->val=child;
        }
        if (!(parentNode = hashGet(nodeHash, parent))) {
            parentNode = malloc(sizeof(TreeNode));
            parentNode->left=NULL;
            parentNode->right=NULL;
            parentNode->val=parent;
        }
        //1、设置左子树
        if (getState)
            parentNode->left = childNode;
        else
            parentNode->right = childNode;
        //放入哈希表
        hashPut(nodeHash, parent, parentNode);
        hashPut(nodeHash, child, childNode);
        //判断parent节点是否为parent，如果不是不要动，否则添加parent=1
        int isp = (int) hashGet(hashParent, parent);
        //如果parent还没有或者不是子节点,记录
        if (isp != 2)
            hashPut(hashParent, parent, (VOID) 1);
        //设置child为2
        hashPut(hashParent, child, (VOID) 2);
    }
    //查找根节点，遍历hashParent,没有parent，值=1的则为根节点
    int key;
    for (i = 0; i < descriptionsSize && (int) hashGet(hashParent, key = descriptions[i][0]) != 1; ++i);
    TREENODE rest = hashGet(nodeHash, key);
    hashFree(hashParent);
    hashFree(nodeHash);
    return rest;
}

int main() {
    int a1[]={20,15,1};
    int a2[]={ 20,17,0};
    int a3[]={50,20,1};
    int a4[]={50,80,0};
    int a5[]={80,19,1};
    int *arr[]={a1, a2, a3, a4, a5};
    TREENODE tree= createBinaryTree(arr,5,(int*)3);
    return 0;
}
