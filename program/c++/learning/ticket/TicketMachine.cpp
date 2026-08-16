//
// Created by Administrator on 2026/7/2.
//

#include "TicketMachine.h"

#include <iostream>
using namespace std;

TicketMachine::TicketMachine() {
    balance = 100;
    cout << this << " 初始化完成: balance = " << balance << endl;
}


TicketMachine::TicketMachine(int init_balance) : balance(init_balance) {
    this->balance = init_balance;
}

int TicketMachine::getBnc(TicketMachine *ticket_machine) {
    return ticket_machine->balance;
}

TicketMachine::~TicketMachine() {
    cout << "该对象: " << this << " 被析构..." << endl;
}

void TicketMachine::showBlance() {
    cout << "this : " << this << endl;
    cout << "balance = " << this->balance << endl;
}

void TicketMachine::insertMoney(int money) {
    this->balance += money;
}
