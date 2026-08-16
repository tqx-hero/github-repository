#include <ctime>
#include <iostream>
using namespace std;

int create_random() {
    srand(time(0));
    return rand() % 100;
}

void guess_number(int result) {
    int num;
    while (true) {
        cout << "请输入数字:" << endl;
        cin >> num;
        //比较与实际数字的大小，给出相应提示
        if (num == result) {
            cout << "恭喜你猜对了!" << endl;
            return;
        }
        if (num < result) {
            cout << "猜小了!" << endl;
        } else
            cout << "猜大了!" << endl;
    }
}

// int main() {
//     int which;
//     while (true) {
//         cout << "请输入:  【 0】:开始 【1】:结束" << endl;
//         cin >> which;
//         if (which == 0) {
//             //生成随机数，传入函数内开始游戏
//             guess_number(create_random());
//         } else if (which == 1) {
//             break;
//         } else
//             cout << "请输入有效数字!" << endl;
//     }
//     return 0;
// }
