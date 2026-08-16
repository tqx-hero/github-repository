//
// Created by Administrator on 2026/7/20.
//
#include <string>

namespace practice {
    using namespace std;

    class MutableTest {
    public:
        MutableTest(const string &name, int age)
            : age(age), num(0), name(name) {
        }

        mutable int age; //mutable修饰的成员变量可以无视const对象不能修改的特点
        int num;
        string name;
    };
}

// int main() {
//     using namespace practice;
//     const MutableTest mt("张三", 100);
//     //age被mutable修饰，可以通过常量对象来修改该变量值
//     mt.age = 10;
//     MutableTest *mptr = const_cast<MutableTest *>(&mt);
//     mptr->num = 100;
//     int *iptr = const_cast<int *>(reinterpret_cast<const int *>(&mt));
//     *++iptr = 30;
//     return 0;
// }
