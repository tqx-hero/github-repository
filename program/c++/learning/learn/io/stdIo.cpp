//
// Created by Administrator on 2026/7/18.
//
#include <iostream>

// int main() {
//     using namespace std;
//     // char ch;
//     //把缓冲区中的一个字符读取到ch中
//     // while ((ch=cin.get()) !=EOF) {
//     //     cout << ch << endl;
//     // }
//     //另一种把缓冲区的字符输入到ch中的函数
//     // char ch2;
//     // while (cin.get(ch2)) {
//     //     cout << ch2 << endl;
//     //     if (ch2 == '\t')
//     //         break;
//     // }
//
//     //把字符读取到数组中，该方式读取到\n进行截断，把数组最后补上\0返回，但是不会把缓冲区内的\n读出来
//     //所以需要后面再添加一个get()，把\n读取出来
//     // char buffer[1024];
//     // while (cin.get(buffer, 1024).get()) {
//     //     cout << buffer << endl;
//     // }
//
//     //读取一行字符串，遇到换行截断
//     //同样不会把换行读到字符串内，但是它把换行读出了缓冲区，所以不需要再像上述操作那样紧接着额外读出换行符
//     // char buf[1024];
//     // while (cin.getline(buf, 1024)) {
//     //     cout << buf;
//     // }
//
//     // char ch3;
//     // cin.get(ch3);
//     // cout << ch3 << endl;
//     // // cin.ignore(2); //忽略若干字符，参数可以写具体几个字符，默认是1个
//     // cin.ignore(10,'\n');    //忽略若干字符，如果在途中出现\n，则仅忽略\n之前的字符,其实就是2个参数取最小的忽略长度
//     // cin.get(ch3);
//     // cout << ch3 << endl;
//
//     // char ch4;
//     // ch4= cin.peek();    //只读出缓冲区内第一个字符的内容，但是队列指针不往前移动，字符没有拿出来，后面再次用get读取，仍然读取的是第一个字符
//     // cout << ch4<< endl;
//     // cin.get(ch4);
//     // cout << ch4<< endl;
//
//     char ch5, buf5[1024];
//     ch5 = cin.peek();
//     cin.putback(ch5);   //将字符ch5放回到缓冲区。默认是把字符放到缓冲区的队列头部。不是放到尾部(putback是放回的意思，不是放到尾部的意思)
//     while (cin.getline(buf5, 1024)) {
//         cout << buf5 << endl;
//     }
//     return 0;
// }
