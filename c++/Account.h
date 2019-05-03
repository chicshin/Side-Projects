#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_

class Account
{
    int accID;
    int balance;
    char * cusName;
public:
    Account(int ID, int money, const char * name);
    Account(const Account &ref);

    int GetAccID() const;
    virtual void Deposit(int money);
    int Withdraw(int money);
    void ShowAccInfo() const;
    ~Account();
};

#endif
