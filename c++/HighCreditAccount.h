#ifndef __HIGHCREDIT_ACCOUNT_H__
#define __HIGHCREDIT_ACCOUNT_H__

#include "NormalAccount.h"

class HighCreditAccount : public NormalAccount
{
    int specialRate;
public:
    HighCreditAccount(int ID, int money, const char * name, int rate, int special)
        :NormalAccount(ID, money, name, rate), specialRate(special)
    {}

    virtual void Deposit(int money)
    {
        Account::Deposit(money);
        Account::Deposit(money*(specialRate/100.0));
    }
};
#endif
