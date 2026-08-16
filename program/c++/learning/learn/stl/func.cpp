//
// Created by Administrator on 2026/7/18.
//

#include <iostream>
#include <set>

//仿函数，其实就是重写操作符(),在以对象调用函数时可以写成obj(parm1,parm2,...)形式
//但实际上是调用的类的重载操作符()
namespace my_std {
    template<typename T>
    struct Compared {
        //仿函数在红黑树生成、节点的插入、查找时，根据函数的比较大小的返回值来确定哪个节点在左边
        //如果不添加仿函数，默认小的放在左边，就是常见的二叉搜索树的结构，即：左<根<右
        //因为set是不允许有重复元素的，所以这里的排序使用的key必须唯一
        auto operator()(const T &i1, const T &i2) const -> decltype(i1 > i2) {
            return i1 > i2;
        }

        //但如果重写的仿函数是以下形式，i1>=i2时返回true，那生成树时会将大的节点放在左边
        //结果就是：左>根>右
        // auto operator()(const T &i1, const T &i2) const -> decltype(i1 >= i2) {
        //     return i1 > i2;
        // }
    };
}

namespace my_persion_f {
    class Persion {
    public:
        Persion(int age, double salary, const std::string &name)
            : age(age),
              salary(salary),
              name(name) {
        }

        Persion(const Persion &other)
            : age(other.age),
              salary(other.salary),
              name(other.name) {
        }


        ~Persion() {
        }

        auto operator>(const Persion &other) const -> decltype(false) {
            return this->salary > other.salary;
        }

        auto operator<(const Persion &other) const -> decltype(false) {
            return this->salary < other.salary;
        }

        const bool operator==(const Persion &other) const {
            return this->salary == other.salary;
        }

        const _STD string &getName() const {
            return this->name;
        }

    private:
        int age;
        double salary;
        _STD string name;
    };
}

// int main() {
//     // using MyCompared_Int = my_std::Compared<int>;
//     // _STD set<int, MyCompared_Int> set;
//     // set.insert(20);
//     // set.insert(10);
//     // set.insert(200);
//     // set.insert(120);
//     // set.insert(320);
//     // for (auto &p: set) {
//     //     _STD cout << p << _STD endl;
//     // }
//     using My_Persion = my_persion_f::Persion;
//     _STD set<My_Persion, my_std::Compared<My_Persion> > pSet;
//     pSet.insert(My_Persion(30, 3000.0f, "张三"));
//     pSet.insert(My_Persion(31, 2500.0f, "李四"));
//     pSet.insert(My_Persion(32, 8000.0f, "王五"));
//     pSet.insert(My_Persion(33, 2000.0f, "赵六"));
//
//     // auto bg = pSet.begin(), ed = pSet.end();
//     // while (bg != ed) {
//     //     _STD cout << bg->getName() << _STD endl;
//     //     ++bg;
//     // }
//     //find时是根据仿函数中的key来查找，即用哪个字段排的序，就以哪个字段为key查找
//     My_Persion sc(30, 2500.0f, "李");
//     // auto it = pSet.find(sc);
//     // if (it != pSet.end())
//     //     _STD cout << it->getName() << _STD endl;
//
//     //lower_bound
//     auto it = pSet.lower_bound(sc); //找到第一个大于等于key的指针
//     // if (it != pSet.end())
//     //     _STD cout << it->getName() << _STD endl;
//     // //指针++,按照中序遍历的步骤，当仿函数使用降序组成红黑树时，指针++后的值必定小于当前值，所以以下输出的是小于2500的赵六
//     // _STD cout << (++it)->getName() << _STD endl;
//
//     //upper_bound,找到第一个严格大于该节点的指针
//     //注意，这里是指针，即红黑树上的节点所在位置，按照中序遍历的规则来返回，即总是返回要查找节点的后继节点。
//     //如果仿函数是降序生成的红黑树，那返回的节点值必然小于要查找的值
//     it = pSet.upper_bound(sc);
//     if (it != pSet.end())
//         _STD cout << it->getName() << _STD endl;
//     return 0;
// }
