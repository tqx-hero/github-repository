//
// Created by Administrator on 2026/7/5.
//

#ifndef C___LINT3779_H
#define C___LINT3779_H


/**
* 3779 · 创建 Animals 类
C++
简单
通过率
46%

题目
题解21
笔记
讨论
排名
记录
描述
在本题中，你需要对 Animals 类的 成员变量 和 成员函数 进行补充。

其中，所需的成员变量有 3 个：

string species：用来表示动物的种类，如："Dog"、"Cat" 等
int id：用来表示动物的编号
int total：用来计算 Animals 类的所有实例化对象的数量
当对 Animals 类进行实例化时，我们会 先后传入 species 和 id 来创建对象，如：Animals dog("Dog", 1)。并且 每次 进行实例化时，total 都应该进行自递增。请创建对应的构造函数。

另外，你还需要创建一个成员函数 printInfo()，用来打印某个 Animals 对象的信息。以上述的 dog 对象为例，当调用 dog.printInfo() 时，控制台会打印如下内容：

New animal -> Species: Dog, ID: 1
样例
输入数据由 构造 Animals 对象的参数 组成一个数组，使用双括号 () 包裹 species 和 id 组成数组中的每一个元素，每个元素之间用逗号 , 进行分割。

评测机将使用数组中的每一个元素来创建 Animals 实例对象，并调用 printInfo() 函数进行信息打印。最后，还会调用 Animals::total 来检查实例化对象的个数是否正确。

样例一

输入

[(Dog, 1)]
输出

New animal -> Species: Dog, ID: 1
Total animals: 1
样例二

输入

[(Dog, 1), (Cat, 2), (Rabbit, 3)]
输出

New animal -> Species: Dog, ID: 1
New animal -> Species: Cat, ID: 2
New animal -> Species: Rabbit, ID: 3
Total animals: 3
推荐课程
 */
#include <iostream>
using namespace std;

class Animals {
public:
    Animals(const string &species, int id);

    Animals();

    virtual ~Animals();

    void printInfo();

    static int total;

private:
    int id;
    string species;
};

int Animals::total = 0;

#endif //C___LINT3779_H
