//
// Created by Administrator on 2026/7/2.
//

#include "./TicketMachine.h"
#include <iostream>
using namespace std;

TicketMachine::TicketMachine() {

}

TicketMachine::~TicketMachine() {

}

void TicketMachine::insertMoney(int money) {
    this->money = money;
    balance+=money;
}

void TicketMachine::showBalance() {
    cout << "balance = " << this->balance << endl;
}
