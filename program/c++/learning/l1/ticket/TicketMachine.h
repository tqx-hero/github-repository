//
// Created by Administrator on 2026/7/2.
//

#ifndef LEARNING_TICKETMACHINE_H
#define LEARNING_TICKETMACHINE_H


class TicketMachine {
public:
    TicketMachine();

    virtual ~TicketMachine();

    void showBalance();

    void insertMoney(int money);

private:
    int money;
    int balance;
};


#endif //LEARNING_TICKETMACHINE_H
