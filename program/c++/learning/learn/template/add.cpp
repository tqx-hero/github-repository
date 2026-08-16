//
// Created by Administrator on 2026/7/16.
//
#include <iostream>
#if 0
class ATmp {
    int num;

public:
    explicit ATmp(int num)
        : num(num) {
    }

    ATmp() : num(0) {
    };

    [[nodiscard]] int getNum() const {
        return num;
    }

    ~ATmp() {
    }

    ATmp operator+(const ATmp &a) const {
        ATmp temp;
        temp.num = this->num + a.num;
        return temp;
    }
};

std::ostream &operator<<(std::ostream &os, const ATmp &a) {
    os << a.getNum();
    return os;
}

//模板函数可以进行重载，如果普通函数与模板函数都匹配参数列表
//编译器会优先调用普通函数，就避免再次利用模板生成一个函数
template<class T>
T myAdd(T &x, T &y) {
    using namespace std;
    cout << "调用的模板函数" << endl;
    return x + y;
}


int myAdd(int &x, int &y) {
    using namespace std;
    cout << "调用的普通函数" << endl;
    return x + y;
}


void test01() {
    int x = 10, y = 20;
    //默认调用的普通函数
    myAdd(x, y);
}

void test02() {
    int x=10,y=20;
    //添加<>表示需要调用模板函数
    myAdd<>(x,y);
}

void test() {
    using namespace std;
    ATmp a(10), b(20);
    const ATmp c = myAdd(a, b);
    cout << c << endl;
}
#endif

// int main() {
//     // test();
//     //默认调用的普通函数
//     // test01();
//     test02();
//     return 0;
// }
