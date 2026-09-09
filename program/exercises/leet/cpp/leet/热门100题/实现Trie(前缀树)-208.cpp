//
// Created by 田庆新 on 2026/9/9.
//
/**
* 208. 实现 Trie (前缀树)
中等
相关标签
premium lock icon
相关企业
Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。

请你实现 Trie 类：

Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。


示例：

输入
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出
[null, null, true, false, true, null, true]

解释
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 True
trie.search("app");     // 返回 False
trie.startsWith("app"); // 返回 True
trie.insert("app");
trie.search("app");     // 返回 True


提示：

1 <= word.length, prefix.length <= 2000
word 和 prefix 仅由小写英文字母组成
insert、search 和 startsWith 调用次数 总计 不超过 3 * 104 次
 * @return
 */
#include <string>
#include <iostream>
#include <array>
using namespace std;

class Trie {
    struct TrieNode {
        char index;
        bool end;
        array<TrieNode *, 26> next;

        TrieNode(char index, bool end = false)
            : index(index), end(end) {
            next.fill(nullptr);
        }
    };

    //根节点
    TrieNode *root = nullptr;

    static bool find_prev(string &word, TrieNode *&prev) {
        for (auto ch: word) {
            if (!prev->next[ch - 'a'])
                return false;
            prev = prev->next[ch - 'a'];
        }
        return true;
    }

public:
    Trie() {
        root = new TrieNode(-1);
    }

    void insert(string word) {
        TrieNode *prev = root;
        for (auto ch: word) {
            //如果字符不存在，创建节点，设置字符
            auto &arr = prev->next;
            if (arr[ch - 'a'] == nullptr)
                arr[ch - 'a'] = new TrieNode(ch);
            prev = arr[ch - 'a'];
        }
        prev->end = true;
    }

    bool search(string word) {
        TrieNode *prev = root;
        if (!find_prev(word, prev))
            return false;
        return prev->end;
    }

    bool startsWith(string prefix) {
        TrieNode *prev = root;
        return find_prev(prefix, prev);
    }
};

// int main() {
//     /*输入
// ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
// [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
// 输出
// [null, null, true, false, true, null, true]
//
// 解释
// Trie trie = new Trie();
// trie.insert("apple");
// trie.search("apple");   // 返回 True
// trie.search("app");     // 返回 False
// trie.startsWith("app"); // 返回 True
// trie.insert("app");
// trie.search("app");     // 返回 True*/
//     Trie tr;
//     tr.insert("apple");
//     cout << tr.search("apple") << endl;
//     cout << tr.search("app") << endl;
//     cout << tr.startsWith("app") << endl;
//     tr.insert("app");
//     cout << tr.search("app") << endl;
//     return 0;
// }
