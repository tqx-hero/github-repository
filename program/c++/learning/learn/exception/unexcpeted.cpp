//
// Created by Administrator on 2026/7/22.
//

#include <iostream>
using namespace std;

class MyExec : public exception {
public:
    explicit MyExec(char const *_Message)
        : exception(_Message) {
    }

    [[nodiscard]] const char *what() const noexcept override {
        return exception::what();
    }
};
//千万不要在回调函数内部继续抛异常，否则会递归调用terminate函数，导致栈溢出
//这是terminate函数的内部实现原理：
/*void std::terminate() noexcept
{
    terminate_handler handler = get_current_terminate_handler();
    if (handler) {
        handler(); // 调用你自定义函数
    }
    // ✅ 关键！只要handler执行完毕返回，走到这里
    std::abort();
}*/
void myExc() {
    cout << "调用了自定义的unexpected" << endl;
    // throw MyExec("出现未知异常....");
}

// int main() {
//     //设置无法修复的异常在结束程序之前的回调函数。
//     //通过以下设置可以设置回调函数，当程序终止之前可以进行一些处理工作
//     //但是处理有限，由于定义的函数不能传参，没有返回值，除了做一些日志统计工作也没多大的用处
//     //执行完自己的回调函数后，会自动调用abort，终止程序
//     auto handler = set_terminate(myExc);
//     try {
//         throw out_of_range("越界异常");
//     } catch (bad_alloc &e) {
//         cout << e.what() << endl;
//     }
//     set_terminate(handler);
//     return 0;
// }
