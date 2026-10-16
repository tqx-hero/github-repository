//
// Created by Administrator on 2026/6/26.
//

/**
* 388. 文件的最长绝对路径
中等
相关标签
premium lock icon
相关企业
假设有一个同时存储文件和目录的文件系统。下图展示了文件系统的一个示例：



这里将 dir 作为根目录中的唯一目录。dir 包含两个子目录 subdir1 和 subdir2 。subdir1 包含文件 file1.ext 和子目录 subsubdir1；subdir2 包含子目录 subsubdir2，该子目录下包含文件 file2.ext 。

在文本格式中，如下所示(⟶表示制表符)：

dir
⟶ subdir1
⟶ ⟶ file1.ext
⟶ ⟶ subsubdir1
⟶ subdir2
⟶ ⟶ subsubdir2
⟶ ⟶ ⟶ file2.ext
如果是代码表示，上面的文件系统可以写为 "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" 。'\n' 和 '\t' 分别是换行符和制表符。

文件系统中的每个文件和文件夹都有一个唯一的 绝对路径 ，即必须打开才能到达文件/目录所在位置的目录顺序，所有路径用 '/' 连接。上面例子中，指向 file2.ext 的 绝对路径 是 "dir/subdir2/subsubdir2/file2.ext" 。每个目录名由字母、数字和/或空格组成，每个文件名遵循 name.extension 的格式，其中 name 和 extension由字母、数字和/或空格组成。

给定一个以上述格式表示文件系统的字符串 input ，返回文件系统中 指向 文件 的 最长绝对路径 的长度 。 如果系统中没有文件，返回 0。



示例 1：


输入：input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
输出：20
解释：只有一个文件，绝对路径为 "dir/subdir2/file.ext" ，路径长度 20
示例 2：


输入：input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
输出：32
解释：存在两个文件：
"dir/subdir1/file1.ext" ，路径长度 21
"dir/subdir2/subsubdir2/file2.ext" ，路径长度 32
返回 32 ，因为这是最长的路径
示例 3：

输入：input = "a"
输出：0
解释：不存在任何文件
示例 4：

输入：input = "file1.txt\nfile2.txt\nlongfile.txt"
输出：12
解释：根目录下有 3 个文件。
因为根目录中任何东西的绝对路径只是名称本身，所以答案是 "longfile.txt" ，路径长度为 12


提示：

1 <= input.length <= 104
input 可能包含小写或大写的英文字母，一个换行符 '\n'，一个制表符 '\t'，一个点 '.'，一个空格 ' '，和数字。
 * @return
 */
//构建一棵目录树，统计它们的有效文件长度即可

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DirNode {
    //当前目录/文件的绝对路径长度。注意目录需要带上/计算
    int len;
    //兄弟节点表示法
    struct DirNode *child, *next;
} DirNode;

DirNode *init_node() {
    DirNode *node = malloc(sizeof(DirNode));
    if (!node) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    node->len = 0;
    node->child = node->next = NULL;
    return node;
}

static inline int max(int x, int y) {
    return x >= y ? x : y;
}

void freeNode(DirNode *sentinel) {
    if (!sentinel)
        return;
    freeNode(sentinel->child);
    freeNode(sentinel->next);
    sentinel->child = sentinel->next = NULL;
    free(sentinel);
    sentinel = NULL;
}

void update_File_Info(DirNode *sentinel, int *sub_len, int *isDir, int *level, int *max_len) {
    DirNode *node = init_node(), *cur = sentinel;
    //文件长度：目录需要加上/,文件名不需要添加
    while ((*level)--)
        cur = cur->child;
    node->next = cur->child;
    cur->child = node;
    node->len = cur->len + (*isDir ? *sub_len + 1 : *sub_len);
    if (!*isDir)
        *max_len = max(node->len, *max_len);
    //清除所有状态，重新计数
    *sub_len = 0;
    *isDir = 1;
    *level = 0;
}

int lengthLongestPath(char *input) {
    int i = 0, sub_len = 0, isDir = 1, level = 0, max_len = 0;
    char ch;
    DirNode *sentinel = init_node();
    for (; (ch = input[i]) != '\0'; i++) {
        //字符等于\n,这个文件或目录到此结束，可以进行截取处理
        if (ch == '\n')
            update_File_Info(sentinel, &sub_len, &isDir, &level, &max_len);
        else if (ch == '\t')
            level++;
        else {
            //如果文件名包含.，说明它不是目录，而是有效文件
            if (ch == '.')
                isDir = 0;
            sub_len++;
        }
    }
    update_File_Info(sentinel, &sub_len, &isDir, &level, &max_len);
    freeNode(sentinel);
    return max_len;
}

int main() {
    char *input = "file1.txt\nfile2.txt\nlongfile.txt";
    // char *input = "a";
    // char *input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
    // char *input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext";
    printf("%d\n", lengthLongestPath(input));
    return 0;
}
