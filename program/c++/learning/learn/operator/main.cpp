//
// Created by Administrator on 2026/7/11.
//
#include <iostream>
using namespace std;
#if 0
class A {
    int numa;
    int numb;

public:
    A(int numa, int numb)
        : numa(numa),
          numb(numb) {
    }

    void print() {
        cout << "numa = " << this->numa << ",numb = " << this->numb << endl;
    }

    //重载运算符++
    //后置++,a++，a后面没有数据，为了与前置++区分开，需要添加占位符int
    //后置++在调用完成后生成的是一个匿名对象，不能再次作为左值继续进行其他操作，所以必须用const修饰
    const A operator++(int) {
        // cout << "x = " << x << endl;
        cout << "int ++" << endl;
        A tmp(*this);
        this->numa++;
        this->numb++;
        return tmp;
    }

    //前置++，++a，a本身就是操作对象，所以不传参
    A &operator++() {
        cout << "no ++" << endl;
        this->numa++;
        this->numb++;
        return *this;
    }

    //如果希望返回值可以再次进行其他后续操作，可以令返回值类型为引用类型
    //适合链式调用
    A &operator+=(A &ann) {
        this->numa += ann.numa;
        this->numb += ann.numb;
        return *this;
    }

    //友元函数最有用的场景，全局重载对象的标准输出格式,保持输出流的语义正确
    //如果不用友元函数，那就提供get、set函数，供外部调用
    // friend ostream &operator<<(ostream &lhs, const A &a);

    //或者直接写在类中，作为a类的成员函数
    // ostream &operator<<(ostream &out) {
    //     out << "<< 运算符重载： " << this->numa << ", numb = " << this->numb << endl;
    //     return out;
    // }
};

//可以全局重载操作符 << 用来设置对象的标准输出格式
//再通过友元函数，声明该全局函数为A类的friend
// ostream &operator<<(ostream &lhs, const A &a) {
//     lhs << "<< 运算符重载： numa = " << a.numa << ", numb = " << a.numb << endl;
//     return lhs;
// }

// int main() {
//     A a(10, 20), b(1, 2), c(2, 3);
//     // ((a++) += b) += c;
//     // ++b;
//     a.print();
//     //适合全局重载 <<
//     cout << a << b << c << endl;
//     //适合定义类的函数，重载 <<,但是重载完了只能使用 a << cout 形式，这样违反了输出流cout的语法格式
//     //所以不建议这样，建议用全局重载的形式，保持标准输出的语义。
//     // a.operator<<(cout);
//     // a << cout << endl;
//     return 0;
// }
#endif
