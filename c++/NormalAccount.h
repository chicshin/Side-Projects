#ifndef __NORMAL_ACCOUNT_H__
#define __NORMAL_ACCOUNT_H__

#include "Account.h"

class NormalAccount : public Account
{
    int interestRate;
public:
    NormalAccount(int ID, int money, const char * name, int rate)
        : Account(ID, money, name), interestRate(rate)
    {}

    virtual void Deposit(int money)
    {
        Account::Deposit(money);
        Account::Deposit(money*(interestRate/100.0));
    }
};

#endif
