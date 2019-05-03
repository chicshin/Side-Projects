#include <iostream>
#include <cstring>
using namespace std;
const int NAME_LEN=20;

enum {CREATE=1, DEPOSIT, WITHDRAWL, INQUIRE, EXIT};

enum {LEVEL_A=7, LEVEL_B=4, LEVEL_C=2};

enum {NORMAL=1, CREDIT=2};
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

Account::Account(int ID, int money, const char * name)
    :accID(ID), balance(money)
{
    cusName=new char[strlen(name)+1];
    strcpy(cusName, name);
}

Account::Account(const Account &ref)
    :accID(ref.accID), balance(ref.balance)
{
    cusName=new char[strlen(ref.cusName)+1];
    strcpy(cusName, ref.cusName);
}

int Account::GetAccID() const
{
    return accID;
}

void Account::Deposit(int money)
{
    balance+=money;
}

int Account::Withdraw(int money)
{
    if(balance<money)
        return 0;
    balance-=money;
    return money;
}

void Account::ShowAccInfo() const
{
    cout<<"Account ID: "<<accID<<endl;
    cout<<"Name: "<<cusName<<endl;
    cout<<"Balance: $"<<balance<<endl;
}

Account::~Account()
{
    delete []cusName;
}

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

void AccountHandler::ShowMenu(void) const
{
    cout<<"-----MENU-----"<<endl;
    cout<<"1. Create Account"<<endl;
    cout<<"2. Deposit"<<endl;
    cout<<"3. Withdrawl"<<endl;
    cout<<"4. Show Account Information"<<endl;
    cout<<"5. Exit"<<endl<<endl;
}

void AccountHandler::CreateAccount(void)
{
    int select;
    cout<<"[Choose Normal/Credit Account]"<<endl;
    cout<<"1. Normal Account"<<endl;
    cout<<"2. Credit Account"<<endl;
    cout<<"Choose: ";
    cin>>select;

    if(select==NORMAL)
        CreateNormalAccount();
    else
        CreateCreditAccount();
}

void AccountHandler::CreateNormalAccount(void)
{
    int id;
    char name[NAME_LEN];
    int balance;
    int interestRate;

    cout<<"---Create Normal Account---"<<endl;
    cout<<"Account ID: "; cin>>id;
    cout<<"Name: "; cin>>name;
    cout<<"Deposit: $"; cin>>balance;
    cout<<"Interest Rate: "; cin>>interestRate;
    cout<<endl;

    accArr[accNum++]=new NormalAccount(id, balance, name, interestRate);
}

void AccountHandler::CreateCreditAccount(void)
{
    int id;
    char name[NAME_LEN];
    int balance;
    int interestRate;
    int creditLevel;

    cout<<"---Create Credit Account---"<<endl;
    cout<<"Account ID: "; cin>>id;
    cout<<"Name: "; cin>>name;
    cout<<"Deposit: $"; cin>>balance;
    cout<<"InterestRate: "; cin>>interestRate;
    cout<<"Credit Level(1toA, 2toB, 3toC): "; cin>>creditLevel;
    cout<<endl;

    switch(creditLevel)
    {
    case 1:
        accArr[accNum++]= new HighCreditAccount(id, balance, name, interestRate, LEVEL_A);
        break;
    case 2:
        accArr[accNum++]= new HighCreditAccount(id, balance, name, interestRate, LEVEL_B);
        break;
    case 3:
        accArr[accNum++]= new HighCreditAccount(id, balance, name, interestRate, LEVEL_C);
    }
}

void AccountHandler::DepositMoney(void)
{
    int money;
    int id;
    cout<<"[DEPOSIT]"<<endl;
    cout<<"Account ID: "; cin>>id;
    cout<<"Amount to Deposit: $"; cin>>money;

    for(int i=0; i<accNum; i++)
    {
        if(accArr[i]->GetAccID()==id)
        {
            accArr[i]->Deposit(money);
            cout<<"Deposit Completed"<<endl;
            return;
        }
    }
    cout<<"Invalid Account ID"<<endl<<endl;
}

void AccountHandler::WithdrawMoney(void)
{
    int money;
    int id;
    cout<<"[WITHDRAWL]"<<endl;
    cout<<"Account ID: "; cin>>id;
    cout<<"Amount to Withdrawl: $"; cin>>money;

    for(int i=0; i<accNum; i++)
    {
        if(accArr[i]->GetAccID()==id)
        {
            if(accArr[i]->Withdraw(money)==0)
            {
                cout<<"Insuffienct Amount in Balance"<<endl;
                return;
            }
        }
        cout<<"Withdrawl Completed"<<endl;
        return;
    }
    cout<<"Invalid Account ID"<<endl<<endl;
}

AccountHandler::AccountHandler() : accNum(0) {}

void AccountHandler::ShowAllAccInfo(void) const
{
    for(int i=0; i<accNum; i++)
    {
        accArr[i]->ShowAccInfo();
        cout<<endl;
    }
}

AccountHandler::~AccountHandler()
{
    for(int i=0; i<accNum; i++)
        delete accArr[i];
}

int main(void)
{
    AccountHandler manager;
    int choice;

    while(1)
    {
        manager.ShowMenu();
        cout<<"Select: ";
        cin>>choice;
        cout<<endl;

        switch(choice)
        {
        case CREATE:
            manager.CreateAccount();
            break;
        case DEPOSIT:
            manager.DepositMoney();
            break;
        case WITHDRAWL:
            manager.WithdrawMoney();
            break;
        case INQUIRE:
            manager.ShowAllAccInfo();
            break;
        case EXIT:
            return 0;
        default:
            cout<<"Illegal Selection"<<endl;
        }
    }
    return 0;
}
