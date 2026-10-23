//
// Created by Administrator on 2026/8/7.
//
/**
* 1598. 文件夹操作日志搜集器
简单
相关标签
premium lock icon
相关企业
提示
每当用户执行变更文件夹操作时，LeetCode 文件系统都会保存一条日志记录。

下面给出对变更操作的说明：

"../" ：移动到当前文件夹的父文件夹。如果已经在主文件夹下，则 继续停留在当前文件夹 。
"./" ：继续停留在当前文件夹。
"x/" ：移动到名为 x 的子文件夹中。题目数据 保证总是存在文件夹 x 。
给你一个字符串列表 logs ，其中 logs[i] 是用户在 ith 步执行的操作。

文件系统启动时位于主文件夹，然后执行 logs 中的操作。

执行完所有变更文件夹操作后，请你找出 返回主文件夹所需的最小步数 。



示例 1：



输入：logs = ["d1/","d2/","../","d21/","./"]
输出：2
解释：执行 "../" 操作变更文件夹 2 次，即可回到主文件夹
示例 2：



输入：logs = ["d1/","d2/","./","d3/","../","d31/"]
输出：3
示例 3：

输入：logs = ["d1/","../","../","../"]
输出：0


提示：

1 <= logs.length <= 103
2 <= logs[i].length <= 10
logs[i] 包含小写英文字母，数字，'.' 和 '/'
logs[i] 符合语句中描述的格式
文件夹名称由小写英文字母和数字组成
 * @return
 */
#include <stack>
#include <vector>
#include <string>
using namespace std;

//用一个变量存储层级，最后返回即可
class Solution {
public:
    int minOperations(vector<string> &logs) {
        string prev("../"), cur("./");
        int level = 0;
        for (auto &str: logs) {
            if (str == cur)
                continue;
            if (str == prev)
                level = max(level - 1, 0);
            else
                level++;
        }
        return level;
    }
};

// //用栈存储下标，最后返回栈的深度
// class Solution {
// public:
//     int minOperations(vector<string> &logs) {
//         stack<int> indexStack;
//         string prev("../"), cur("./");
//         int size = static_cast<int>(logs.size());
//         for (int i = 0; i < size; i++) {
//             string &str = logs[i];
//             if (str == prev) {
//                 if (!indexStack.empty())
//                     indexStack.pop();
//             } else if (str == cur) {
//                 continue;
//             } else
//                 indexStack.push(i);
//         }
//         return static_cast<int>(indexStack.size());
//     }
// };

// int main() {
//     return 0;
// }
