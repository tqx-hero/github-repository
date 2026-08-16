//
// Created by Administrator on 2026/7/2.
//

#ifndef LN_TICKETMACHINE_H
#define LN_TICKETMACHINE_H


class TicketMachine {
public:
    TicketMachine();

    TicketMachine(int balance);

    ~TicketMachine();

    void insertMoney(int money);

    void showBlance();

    int getBnc(TicketMachine *ticket_machine);

    // private:
    int balance;
};


#endif //LN_TICKETMACHINE_H
