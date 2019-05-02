#include <iostream>
#include <cstring>
using namespace std;
const int NAME_LEN=20;

enum{CREATE=1, DEPOSIT, WITHDRAWL, INQUIRE, EXIT};

class Account
{
    int accID;
    int balance;
    char * cusName;
public:
    Account(int accID, int balance, char * cusName);
    Account(const Account & copy);

    int GetAccID() const;
    void Deposit(int money);
    int Withdraw(int money);
    void ShowAccInfo() const;
    ~Account();
};

Account::Account(int accID, int balance, char * cusName)
{
    this->accID=accID;
    this->balance=balance;
    this->cusName=new char[strlen(cusName)+1];
    strcpy(this->cusName, cusName);
}

Account::Account(const Account & copy)
{
    this->accID=copy.accID;
    this->balance=copy.balance;
    this->cusName=new char[strlen(copy.cusName)+1];
    strcpy(this->cusName, copy.cusName);
}

int Account::GetAccID() const { return accID; }

void Account::Deposit(int money)
{
    balance+=money;
}

int Account::Withdraw(int money)
{
    if(balance<money)
    {
        return 0;
    }
    balance-=money;
    return money;
}

void Account::ShowAccInfo() const
{
    cout<<"ID: "<<accID<<endl;
    cout<<"Name: "<<cusName<<endl;
    cout<<"Balance: $"<<balance<<endl;
}

Account::~Account()
{
    delete []cusName;
}

class AccountHandler
{
    Account * accArr[100];
    int accNum;
public:
    AccountHandler();
    void ShowMenu(void) const;
    void CreateAccount(void);
    void DepositMoney(void);
    void WithdrawMoney(void);
    void ShowAllInfo(void);
    ~AccountHandler();
};

void AccountHandler::ShowMenu(void) const
{
    cout<<"-----Menu-----"<<endl;
    cout<<"1. Create Account"<<endl;
    cout<<"2. Deposit"<<endl;
    cout<<"3. Withdraw"<<endl;
    cout<<"4. Account Information"<<endl;
    cout<<"5. Quit"<<endl;
}

void AccountHandler::CreateAccount(void)
{
    int id;
    char name[NAME_LEN];
    int balance;

    cout<<"Creating Account"<<endl;
    cout<<"ID: "; cin>>id;
    cout<<"Name: "; cin>>name;
    cout<<"Balance: "; cin>>balance;
    cout<<endl;

    accArr[accNum++]=new Account(id, balance, name);
}

void AccountHandler::DepositMoney(void)
{
    int money;
    int id;

    cout<<"Deposit"<<endl;
    cout<<"ID: "; cin>>id;
    cout<<"Amount to deposit: $"; cin>>money;

    for(int i=0; i<accNum; i++)
    {
        if(accArr[i]->GetAccID()==id)
        {
            accArr[i]->Deposit(money);
            cout<<"Finishing Deposit"<<endl;
            return;
        }
    }
    cout<<"Invalid ID"<<endl;
}

void AccountHandler::WithdrawMoney(void)
{
    int money;
    int id;

    cout<<"Withdrawl"<<endl;
    cout<<"ID: "; cin>>id;
    cout<<"Amount to with drawl: $"; cin>>money;

    for(int i=0; i<accNum; i++)
    {
        if(accArr[i]->GetAccID()==id)
        {
            if(accArr[i]->Withdraw(money)==0)
            {
                cout<<"Balance Insufficient"<<endl;
                return;
            }
            cout<<"Finishing Withrawl"<<endl;
            return;
        }
    }
    cout<<"Invalid Account ID"<<endl;
}

AccountHandler::AccountHandler() : accNum(0) {}

void AccountHandler::ShowAllInfo(void)
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
    {
        delete accArr[i];
    }
}
int main(void)
{
    AccountHandler manager;
    int choice;

    while(1)
    {
        manager.ShowMenu();
        cout<<"Select... ";
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
            manager.ShowAllInfo();
            break;
        case EXIT:
            return 0;
        default:
            cout<<"Invalid Selection"<<endl;
        }
    }
    return 0;
}
