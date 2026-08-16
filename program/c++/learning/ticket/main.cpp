#include <iostream>

#include "TicketMachine.h"
//
// Created by Administrator on 2026/7/2.
//
using namespace std;
//在对象初始化阶段，必须对成员变量设置初始值，虚拟机不会像java那样给成员变量设置默认值。
//所以在构造函数内必须对成员变量进行初始化。
// int main() {
//     // auto *tm = new TicketMachine;
//     // tm->insertMoney(20);
//     // tm->showBlance();
//     // delete tm;
//     // tm = nullptr;
//     TicketMachine *tm = new TicketMachine();
//     // cout << tm->balance << endl;
//     tm->insertMoney(20);
//     tm->showBlance();
//
//
//     TicketMachine tc{};
//     tc.showBlance();
//     // int bnc = tc.getBnc(tm);
//     // cout << "tm :" << bnc << endl;
//     // cout << "tc :" << tc.balance << endl;
//     delete tm;
//     tm = nullptr;
//     return 0;
// }
