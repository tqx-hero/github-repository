//
// Created by Administrator on 2026/7/20.
//
/**
 * 2296. 设计一个文本编辑器
困难
相关标签
premium lock icon
相关企业
提示
请你设计一个带光标的文本编辑器，它可以实现以下功能：

添加：在光标所在处添加文本。
删除：在光标所在处删除文本（模拟键盘的删除键）。
移动：将光标往左或者往右移动。
当删除文本时，只有光标左边的字符会被删除。光标会留在文本内，也就是说任意时候 0 <= cursor.position <= currentText.length 都成立。

请你实现 TextEditor 类：

TextEditor() 用空文本初始化对象。
void addText(string text) 将 text 添加到光标所在位置。添加完后光标在 text 的右边。
int deleteText(int k) 删除光标左边 k 个字符。返回实际删除的字符数目。
string cursorLeft(int k) 将光标向左移动 k 次。返回移动后光标左边 min(10, len) 个字符，其中 len 是光标左边的字符数目。
string cursorRight(int k) 将光标向右移动 k 次。返回移动后光标左边 min(10, len) 个字符，其中 len 是光标左边的字符数目。


示例 1：

输入：
["TextEditor", "addText", "deleteText", "addText", "cursorRight", "cursorLeft", "deleteText", "cursorLeft", "cursorRight"]
[[], ["leetcode"], [4], ["practice"], [3], [8], [10], [2], [6]]
输出：
[null, null, 4, null, "etpractice", "leet", 4, "", "practi"]

解释：
TextEditor textEditor = new TextEditor(); // 当前 text 为 "|" 。（'|' 字符表示光标）
textEditor.addText("leetcode"); // 当前文本为 "leetcode|" 。
textEditor.deleteText(4); // 返回 4
                          // 当前文本为 "leet|" 。
                          // 删除了 4 个字符。
textEditor.addText("practice"); // 当前文本为 "leetpractice|" 。
textEditor.cursorRight(3); // 返回 "etpractice"
                           // 当前文本为 "leetpractice|".
                           // 光标无法移动到文本以外，所以无法移动。
                           // "etpractice" 是光标左边的 10 个字符。
textEditor.cursorLeft(8); // 返回 "leet"
                          // 当前文本为 "leet|practice" 。
                          // "leet" 是光标左边的 min(10, 4) = 4 个字符。
textEditor.deleteText(10); // 返回 4
                           // 当前文本为 "|practice" 。
                           // 只有 4 个字符被删除了。
textEditor.cursorLeft(2); // 返回 ""
                          // 当前文本为 "|practice" 。
                          // 光标无法移动到文本以外，所以无法移动。
                          // "" 是光标左边的 min(10, 0) = 0 个字符。
textEditor.cursorRight(6); // 返回 "practi"
                           // 当前文本为 "practi|ce" 。
                           // "practi" 是光标左边的 min(10, 6) = 6 个字符。


提示：

1 <= text.length, k <= 40
text 只含有小写英文字母。
调用 addText ，deleteText ，cursorLeft 和 cursorRight 的 总 次数不超过 2 * 104 次。


进阶：你能设计并实现一个每次调用时间复杂度为 O(k) 的解决方案吗？
 * @return
 */
#include <iostream>
#include <string>
#include <utility>
using namespace std;

class TextEditor {
public:
    TextEditor() {
        head = new LinkedNode("sentinel", -1);
        tail = new LinkedNode("sentinel", -1);
        head->next = tail;
        tail->prev = head;
        cursor = head;
        offset = -1;
    }

    void addText(string text) {
        //当光标位置出现在最右边时，直接新增节点
        if (cursor == head || offset == cursor->size - 1) {
            LinkedNode *cur = new LinkedNode(text);
            cursor->next->prev = cur;
            cur->next = cursor->next;
            cursor->next = cur;
            cur->prev = cursor;
            offset = cur->size - 1;
            cursor = cur;
        } else {
            string newStr;
            int size = cursor->size, beforeCnt = offset + 1, textCnt = text.size();
            //如果光标出现在字符串中间位置，则需要将字符串重新拼接，在放回cursor节点，不进行节点添加操作
            auto &oldStr = cursor->text;
            newStr.reserve(size + textCnt);
            //将字符串分成2部分，[0~offset]、[offset+1,size-1],在它们中间拼接新字符串
            newStr += oldStr.substr(0, beforeCnt);
            newStr += text;
            if (beforeCnt < size)
                newStr += oldStr.substr(beforeCnt, size - beforeCnt);
            offset += textCnt;
            cursor->text = newStr;
            cursor->size = size + textCnt;
        }
    }

    int deleteText(int k) {
        //光标位置是否是头节点
        //头节点不做操作
        int size, offSize;
        if ((size = cursor->size) == -1) {
            return 0;
        }
        //要删除的长度大于等于光标所在位置到起始点的位置
        //如果光标在当前节点的最右端，先把当前节点删除，光标指向前驱节点，在删除剩余的节点数
        if (k >= (offSize = offset + 1) && offset == cursor->size - 1) {
            cursor = deleteCurNode(cursor);
            offset = cursor->size - 1;
            return size + deleteText(k - offSize);
        }
        //要删除的长度小于当前光标
        //直接在当前节点逻辑删除，即移动右指针即可
        string str, &curStr = cursor->text;
        bool flag;
        int newOffset = offset - k, i;
        if (flag = (k < offSize)) {
            for (i = 0; i <= newOffset; i++)
                str.push_back(curStr.at(i));
            for (i = offSize; i < size; i++)
                str.push_back(curStr.at(i));
        } else {
            //如果光标在中间，则需要删除前半段
            for (i = offSize; i < size; i++)
                str.push_back(curStr.at(i));
        }
        cursor->size = str.size();
        cursor->text = str;
        if (flag) {
            offset = newOffset;
            return k;
        }
        cursor = cursor->prev;
        offset = cursor->size - 1;
        return offSize + deleteText(k - offSize);
    }

    string cursorLeft(int k) {
        //偏移量小于0，表示到头了
        if (k <= 0 || cursor == head) {
            return getStr();
        }
        //超不出这个节点范围
        int count;
        if (k < (count = offset + 1)) {
            offset -= k;
        } else {
            cursor = cursor->prev;
            offset = cursor->size - 1;
            // k--;
        }
        return cursorLeft(k - count);
    }

    string cursorRight(int k) {
        //偏移量小于0，表示到头了
        if (k <= 0) {
            return getStr();
        }
        //先往后移动光标
        int count;
        //如果当前节点后面剩余的字符个数超过k，直接移动光标
        if (k <= (count = cursor->size - offset - 1)) {
            offset += k;
        } else if (cursor->next == tail) {
            offset = cursor->size - 1;
            k = 0;
        } else {
            //当前节点不够时，需要先把当前节点过掉，光标转移到next节点
            cursor = cursor->next;
            offset = 0;
            k--;
        }
        return cursorRight(k - count);
    }

    ~TextEditor() {
        while (head) {
            auto next = head->next;
            delete head;
            head = next;
        }
    }

private:
    struct LinkedNode {
        int size;
        LinkedNode *prev, *next;
        string text;

        explicit LinkedNode(const string &name) : size(name.size()), prev(nullptr),
                                                  next(nullptr)
                                                  , text(name) {
        }

        explicit LinkedNode(string name, int size) : size(size), prev(nullptr),
                                                     next(nullptr)
                                                     , text(std::move(name)) {
        }

        ~LinkedNode() {
            this->prev = nullptr;
            this->next = nullptr;
        }
    };

    void getCountStr(int k, string &str, LinkedNode *cur, int off) {
        if (off < 0 || k == 0)
            return;
        auto &text = cur->text;
        for (int i = off; i >= 0 && k > 0; i--, k--)
            str.push_back(text.at(i));
        if (k > 0) {
            cur = cur->prev;
            off = cur->size - 1;
        }
        getCountStr(k, str, cur, off);
    }

    string getStr() {
        string str;
        getCountStr(10, str, cursor, offset);
        if (str.size())
            std::reverse(str.begin(), str.end());
        return str;
    }

    LinkedNode *deleteCurNode(LinkedNode *cur) {
        //删除当前节点
        auto prev = cur->prev;
        prev->next = cur->next;
        cur->next->prev = prev;
        cur->prev = nullptr;
        cur->next = nullptr;
        delete cur;
        return prev;
    }

    int offset;
    LinkedNode *head, *tail, *cursor;
};

// int main() {
//     /*["TextEditor", "addText",     "deleteText", "addText", "cursorRight", "cursorLeft", "deleteText", "cursorLeft", "cursorRight"]
// [           [],         ["leetcode"],       [4],   ["practice"],      [3],            [8],        [10],        [2],           [6]]
// 输出：
//             [null,       null,               4,         null,       "etpractice", "leet",       4,              "",         "practi"]*/
//
//     TextEditor tx;
//
//     // tx.addText("leetcode");
//     // cout << tx.deleteText(4) << endl; //4
//     // tx.addText("practice");
//     // cout << tx.cursorRight(3) << endl; //etpractice
//     // cout << tx.cursorLeft(8) << endl; //leet
//     // cout << tx.deleteText(10) << endl; //4
//     // cout << tx.cursorLeft(2) << endl; //""
//     // cout << tx.cursorRight(6) << endl; //practi
//
//     /*["TextEditor","addText","cursorLeft","cursorLeft","addText","deleteText"]
//          [[],       ["jxarid"],     [5],        [10],       ["du"],     [20]]
// [null,null,"j","",null,2]*/
//     // tx.addText("jxarid");
//     // cout << tx.cursorLeft(5) << endl; //j
//     // cout << tx.cursorLeft(10) << endl; //""
//     // tx.addText("du");
//     // cout << tx.deleteText(20) << endl; //2
//
//     /*["TextEditor","addText",      "deleteText","addText",     "cursorLeft","addText","deleteText","addText","cursorLeft","deleteText"]
//         [[],    ["arnvmumatgmyw"],      [5],    ["zrlufuifuy"],         [2],    ["unh"],  [20],       ["kwwp"],       [6],        [9]]
//
// [       null,       null,               5,          null,           "mazrlufuif",   null,   19          ,null,      ""          ,0]*/
//
//     // tx.addText("arnvmumatgmyw");
//     // cout << tx.deleteText(5) << endl; //5
//     // tx.addText("zrlufuifuy");
//     // cout << tx.cursorLeft(2) << endl; //mazrlufuif
//     // tx.addText("unh");
//     // cout << tx.deleteText(20) << endl; //19
//     // cout << tx.cursorRight(3) << endl; //etpractice
//
//
//     /*["TextEditor",    "addText"           ,"addText", "cursorLeft",       "addText",      "cursorLeft","addText",             "addText"]
// [       [],             ["ydqikzumibbigl"],["nuvska"]       ,[3],       ["sgtiuhxsnddefr"]      ,[18],["mdpmxkbliikqviikbt"],["lfveldxwzbotb"]]
// 输出
//         [null,          null,                   null,       "mibbiglnuv",       null,           "kzumibbigl",       null,           null]
// 预期结果
// [       null,           null,                   null,       "mibbiglnuv"            ,null,          "ikzumibbig",       null,       null]*/
//
//     tx.addText("ydqikzumibbigl");
//     tx.addText("nuvska");
//     cout << tx.cursorLeft(3) << endl; //mibbiglnuv
//     tx.addText("sgtiuhxsnddefr");
//     cout << tx.cursorLeft(18) << endl; //ikzumibbig
//     tx.addText("mdpmxkbliikqviikbt");
//     tx.addText("lfveldxwzbotb");
//
//     return 0;
// }
