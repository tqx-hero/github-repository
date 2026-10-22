#include "map.h"
/**
 * @brief BKDR字符串哈希函数
 */
// unsigned int hash_func(const char* key)
// {
//     unsigned int seed = 131;
//     unsigned int hash = 0;
//     while (*key)
//     {
//         hash = hash * seed + (*key++);
//     }
//     return hash % HASH_TABLE_SIZE;
// }

unsigned int hash_func(int key)
{
    return ((unsigned int) key) % HASH_TABLE_SIZE;
}

/**
 * @brief 创建哈希表
 */
HashTable* hash_table_create(void)
{
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) return NULL;

    ht->bucket_size = HASH_TABLE_SIZE;
    ht->buckets = (HashNode**)calloc(ht->bucket_size, sizeof(HashNode*));
    if (!ht->buckets)
    {
        free(ht);
        return NULL;
    }
    return ht;
}

/**
 * @brief 插入key‑value，key重复则覆盖旧value
 * value为外部数据，哈希表不拷贝value，只保存指针
 */
int hash_table_put(HashTable* ht, int key, void* value)
{
    if (!ht) return -1;

    unsigned int idx = hash_func(key);
    HashNode* p = ht->buckets[idx];

    // key已存在，覆盖value
    while (p != NULL)
    {
        if (p->key == key)
        {
            p->value = value;
            return 0;
        }
        p = p->next;
    }

    // 新建节点头插法
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    if (!new_node) return -1;

    new_node->key = key; 
    new_node->value = value;
    new_node->next = ht->buckets[idx];
    ht->buckets[idx] = new_node;
    return 0;
}

/**
 * @brief 根据key查找，找不到返回NULL
 */
void* hash_table_get(HashTable* ht, int key)
{
    if (!ht) return NULL;
    unsigned int idx = hash_func(key);
    HashNode* p = ht->buckets[idx];
    while (p != NULL)
    {
        if (p->key == key)
        {
            return p->value;
        }
        p = p->next;
    }
    return NULL;
}

/**
 * @brief 删除key对应的节点
 * 注意：不会释放value指向的内存，由调用者处理
 */
int hash_table_remove(HashTable* ht, int key)
{
    if (!ht) return -1;
    unsigned int idx = hash_func(key);
    HashNode* p = ht->buckets[idx];
    HashNode* prev = NULL;

    while (p != NULL)
    {
        if (p->key ==key)
        {
            if (prev == NULL)
            {
                ht->buckets[idx] = p->next;
            }
            else
            {
                prev->next = p->next;
            }
            free(p);
            return 0;
        }
        prev = p;
        p = p->next;
    }
    return -2; // key不存在
}

/**
 * @brief 遍历哈希表，回调函数接收key、value
 */
void hash_table_foreach(HashTable* ht, HashVisitCb cb)
{
    if (!ht || !cb) return;
    for (int i = 0; i < ht->bucket_size; i++)
    {
        HashNode* p = ht->buckets[i];
        while (p != NULL)
        {
            cb(p->key, p->value);
            p = p->next;
        }
    }
}

/**
 * @brief 销毁整个哈希表
 * 只释放key、节点、桶数组；value内存交给用户释放
 */
void hash_table_destroy(HashTable* ht)
{
    if (!ht) return;
    for (int i = 0; i < ht->bucket_size; i++)
    {
        HashNode* p = ht->buckets[i];
        while (p != NULL)
        {
            HashNode* tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    free(ht->buckets);
    free(ht);
}

// ========== 测试demo ==========
static void print_cb(const char* key, void* value)
{
    int val = *(int*)value;
    printf("key=%-8s val=%d\n", key, val);
}

// int main(void)
// {
//     HashTable* ht = hash_table_create();

//     int a = 100, b = 200, c = 300;
//     hash_table_put(ht, "apple", &a);
//     hash_table_put(ht, "banana", &b);
//     hash_table_put(ht, "cat", &c);

//     printf("====遍历====\n");
//     hash_table_foreach(ht, print_cb);

//     int* find_val = hash_table_get(ht, "banana");
//     if (find_val)
//     {
//         printf("\nget banana = %d\n", *find_val);
//     }

//     hash_table_remove(ht, "cat");
//     printf("\n====删除cat之后====\n");
//     hash_table_foreach(ht, print_cb);

//     hash_table_destroy(ht);
//     return 0;
// }
