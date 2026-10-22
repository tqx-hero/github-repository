//
// Created by Administrator on 2026/6/11.
//

/**
*
￼
代码
￼
测试用例
￼
测试结果
测试结果
12. 整数转罗马数字
￼
中等
￼
相关标签
￼
相关企业
￼
七个不同的符号代表罗马数字，其值如下：
符号
值
I
1
V
5
X
10
L
50
C
100
D
500
M
1000
罗马数字是通过添加从最高到最低的小数位值的转换而形成的。将小数位值转换为罗马数字有以下规则：
• 如果该值不是以 4 或 9 开头，请选择可以从输入中减去的最大值的符号，将该符号附加到结果，减去其值，然后将其余部分转换为罗马数字。
• 如果该值以 4 或 9 开头，使用 减法形式，表示从以下符号中减去一个符号，例如 4 是 5 (V) 减 1 (I): IV ，9 是 10 (X) 减 1 (I)：IX。仅使用以下减法形式：4 (IV)，9 (IX)，40 (XL)，90 (XC)，400 (CD) 和 900 (CM)。
• 只有 10 的次方（I, X, C, M）最多可以连续附加 3 次以代表 10 的倍数。你不能多次附加 5 (V)，50 (L) 或 500 (D)。如果需要将符号附加4次，请使用 减法形式。
给定一个整数，将其转换为罗马数字。 
示例 1：
输入：num = 3749
输出： "MMMDCCXLIX"
解释：
3000 = MMM 由于 1000 (M) + 1000 (M) + 1000 (M)
 700 = DCC 由于 500 (D) + 100 (C) + 100 (C)
  40 = XL 由于 50 (L) 减 10 (X)
   9 = IX 由于 10 (X) 减 1 (I)
注意：49 不是 50 (L) 减 1 (I) 因为转换是基于小数位
示例 2：
输入：num = 58
输出："LVIII"
解释：
50 = L
 8 = VIII
示例 3：
输入：num = 1994
输出："MCMXCIV"
解释：
1000 = M
 900 = CM
  90 = XC
   4 = IV
  提示：
• 1 <= num <= 3999
 * @return
 */

#define HASH_SIZE 41   // 质数，减少冲突
#include <stdio.h>
#include <stdlib.h>

// 哈希结点
typedef struct HashNode {
    int key;
    char *val;
    struct HashNode *next;
} HashNode;

HashNode *hashTable[HASH_SIZE];

// 哈希映射函数
static int hashFunc(int key) {
    return abs(key) % HASH_SIZE;
}

// 初始化哈希表
void hashInit() {
    for (int i = 0; i < HASH_SIZE; i++)
        hashTable[i] = NULL;
}

// 插入/更新
void hashPut(int key, char *val) {
    int idx = hashFunc(key);
    HashNode *cur = hashTable[idx];
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
    newNode->next = hashTable[idx];
    hashTable[idx] = newNode;
}

// 查找，不存在返回null
char *hashGet(int key) {
    int idx = hashFunc(key);
    HashNode *cur = hashTable[idx];
    while (cur) {
        if (cur->key == key)
            return cur->val;
        cur = cur->next;
    }
    return NULL;
}

// 删除键
void hashRemove(int key) {
    int idx = hashFunc(key);
    HashNode **p = &hashTable[idx];
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
void hashFree() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *cur = hashTable[i];
        while (cur) {
            HashNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}

void init() {
    //1~10
    hashPut(1, "I");
    hashPut(2, "II");
    hashPut(3, "III");
    hashPut(4, "IV");
    hashPut(5, "V");
    hashPut(6, "VI");
    hashPut(7, "VII");
    hashPut(8, "VIII");
    hashPut(9, "IX");
    hashPut(10, "X");
    //20~100
    hashPut(20, "XX");
    hashPut(30, "XXX");
    hashPut(40, "XL");
    hashPut(50, "L");
    hashPut(60, "LX");
    hashPut(70, "LXX");
    hashPut(80, "LXXX");
    hashPut(90, "XC");
    hashPut(100, "C");
    //200~1000
    hashPut(200, "CC");
    hashPut(300, "CCC");
    hashPut(400, "CD");
    hashPut(500, "D");
    hashPut(600, "DC");
    hashPut(700, "DCC");
    hashPut(800, "DCCC");
    hashPut(900, "CM");
    hashPut(1000, "M");
    //2000~3000
    hashPut(2000, "MM");
    hashPut(3000, "MMM");
}

char *intToRoman(int num) {
    hashInit();
    init();
    char *ret = malloc(20);
    //处理num
    int div = 1000, i = 0;
    while (div) {
        int res = num / div;
        if (res) {
            char *str = hashGet(res * div);
            char c;
            for (int j = 0; (c = *(str + j)) != '\0'; ++j, i++) {
                *(ret + i) = c;
            }
        }
        num %= div;
        div /= 10;
    }
    *(ret+i) ='\0';
    hashFree();
    return ret;
}

int main() {
    int a =1994;
    char * ret = intToRoman(a);
    printf("%s\n",ret);
    free(ret);
    return 0;
}
