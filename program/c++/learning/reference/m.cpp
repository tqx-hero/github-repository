//
// Created by Administrator on 2026/7/5.
//

class A {
public:
    int a, b;

    A() : a(0), b(1) {
    }
};

A f() {
    A a;
    return a;
}

// int main() {
//     //这里是把f函数栈内生成的局部对象进行了拷贝，拷贝到了main函数栈内赋值给了一个叫cc的对象
//     A cc = f();
//     cc.a = 10;
//     cc.b = 20;
//     return 0;
// }
