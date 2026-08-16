//
// Created by Administrator on 2026/7/11.
//

#include <cstdlib>
#include <iostream>
using namespace std;

class A {
    int num;

public:
    explicit A(int num)
        : num(num) {
        cout << "调用了类的有参构造函数" << endl;
    }

    A() = default;

    //重载new操作符，参数为字节数，返回值类型必须为void*
    //编译器会先解析对象所占空间大小(单位为字节),调用重载后的new。
    //再去调用类的有参构造或无参构造
    //这里的size_t是编译器直接通过sizeof(A)计算出来的字节大小
    //如果是new[10]，那这个size_t也是数组的总大小，计算方式： sizeof(A[10])
    void *operator new(size_t size) {
        cout << size << endl;
        return malloc(size);
    }

    ~A() {
        cout << "调用了析构函数" << endl;
    }

    //delete释放内存空间，在调用之前编译器先调用析构函数
    void operator delete(void *p) {
        cout << "重载delete函数被调用" << endl;
        free(p);
    }

    //delete[]在调用之前，编译器还是会先调用对象的析构函数
    //即遍历数组，依次调用每个数组元素的析构函数。
    //调用完成后再执行这个delete[]函数,释放内存空间。
    void operator delete[](void *p) {
        cout << "重载delete[]被调用" << endl;
        free(p);
    }
};

//调用顺序： new -> A() -> ~A() -> delete
// int main(int argv, char **args, char **envs) {
//     // A *a = (A *) new A(20);
//     // delete a;
//
//     A *arr = (A *) new A[5];
//     delete[] arr;
//     return 0;
// }
