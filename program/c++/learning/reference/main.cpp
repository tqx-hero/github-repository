//
// Created by Administrator on 2026/7/4.
//

#include <iostream>
using namespace std;
//与指针比较类似，都是传递的实参所在的内存单元
//传递过来后，这里的形参就是实参的一个引用，也就是别名
//在函数里面对这个引用做一些修改，也就是对这个内存区域直接修改
//修改完成后相对应的实参也会改变。
//没有解引用，看起来比指针更清爽
void modify(int &a) {
    a++;
}

// int &modiy(int &ax) {
//     return ax;
// }

// int main() {
//     //&是对等号后面的对象的引用，其实就是该对象名称的别名，是对同一块内存地址的别名
//     // char s = 'a';
//     // char &s1 = s;
//     // std::cout << "s1 = " << s1 << std::endl;
//     //&p=s后，p就是s的一个别名，他俩都是同一块内存区域的名称
//     int s = 10, n = 20; //对变量s进行赋值操作： mov dword[rbp - 20],10
//     int &p = s; //对变量p进行赋值操作，把s的内存地址传入p作为p的值:lea rax,[rbp-20]   mov dword [rbp-16],rax
//     //p=n是赋值操作，也就是把n的值赋值给p，也就是赋值给s
//     p = n;
//     //引用一旦初始化，绑定某个变量名以后，就无法再修改，这点与指针有巨大差别的
//     // &p =n;
//     modify(s); // 这里直接把s变量表示的内存单元地址传入了函数 lea rax, [rbp-20]
//     // modify(p); //这个转成汇编时，直接把p所在的内存单元值传递给了函数，而p内存单元记录的就是s变量的地址： mov rax,[rbp-16]
//     std::cout << "s = " << s << std::endl;
//     cout << "p =" << p << endl;
//     return 0;
// }

// int &f(int &a) {
//     int &b = a;
//     b += 2;
//     return b;
// }
//
// int main() {
//     int a = 20;
//     f(a);
//     cout << "a = " << a << endl;
//     return 0;
// }
