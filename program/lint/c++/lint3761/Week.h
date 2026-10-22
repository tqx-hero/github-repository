//
// Created by Administrator on 2026/7/5.
//

#ifndef C___WEEK_H
#define C___WEEK_H


/**
* 3761 · 定义工作日和周末的枚举
C++
入门
通过率
62%

题目
题解13
笔记
讨论2
排名
记录
描述
在 week.cpp 文件中，需要你完成 2 个枚举的定义：

Weekday：需要定义 MONDAY、TUESDAY、WEDNESDAY、THURSDAY 和 FRIDAY 五个 枚举成员，使用 默认值
Weekend：需要定义 SATURDAY 和 SUNDAY 两个 枚举成员，它们的值分别为 6 和 7
Main.cpp 中，将对它们以 Weekday:: 或 Weekend:: 的形式进行使用，具体逻辑可在文件中进行查看。

样例
本题 不需要任何形式的输入，如果你的代码编写正确，控制台将输出：

0 1 2 3 4
6 7
相关知识
 */

enum Weekday {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY
};

enum Weekend {
    SATURDAY = 6,
    SUNDAY = 7
};


#endif //C___WEEK_H
