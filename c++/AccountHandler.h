#ifndef __ACCOUNT_HANDLER_H__
#define __ACCOUNT_HANDLER_H__

#include "Account.h"

class AccountHandler
{
    Account* accArr[100];
    int accNum;
public:
    AccountHandler();
    void ShowMenu(void) const;
    void CreateAccount(void);
    void DepositMoney(void);
    void WithdrawMoney(void);
    void ShowAllAccInfo(void) const;
    ~AccountHandler();
protected:
    void CreateNormalAccount(void);
    void CreateCreditAccount(void);
};
#endif
