#include <iostream>
#include <cstring>
using namespace std;
const int NAME_LEN=20;

void ShowMenu(void);
void CreateAccount(void);
void DepositMoney(void);
void WithdrawMoney(void);
void ShowAllInfo(void);

enum{CREATE=1, DEPOSIT, WITHDRAWL, INQUIRE, EXIT};

class Account
{
    int accID;
    int balance;
    char * cusName;
public:
    Account(int accID, int balance, char * cusName)
    {
        this->accID=accID;
        this->balance=balance;
        this->cusName=new char[strlen(cusName)+1];
        strcpy(this->cusName, cusName);
    }

    Account(const Account & copy)
    {
        this->accID=copy.accID;
        this->balance=copy.balance;
        this->cusName=new char[strlen(copy.cusName)+1];
        strcpy(this->cusName, copy.cusName);
    }

    int GetAccID() { return accID; }

    void Deposit(int money)
    {
        balance+=money;
    }

    int Withdraw(int money)
    {
        if(balance<money)
        {
            return 0;
        }
        balance-=money;
        return money;
    }

    void ShowAccInfo()
    {
        cout<<"ID: "<<accID<<endl;
        cout<<"Name: "<<cusName<<endl;
        cout<<"Balance: $"<<balance<<endl;
    }

    ~Account()
    {
        delete []cusName;
    }
};

Account * accArr[100];
int accNum=0;


int main(void)
{
    int choice;

    while(1)
    {
        ShowMenu();
        cout<<"Select... ";
        cin>>choice;
        cout<<endl;

        switch(choice)
        {
        case CREATE:
            CreateAccount();
            break;
        case DEPOSIT:
            DepositMoney();
            break;
        case WITHDRAWL:
            WithdrawMoney();
            break;
        case INQUIRE:
            ShowAllInfo();
            break;
        case EXIT:
            return 0;
        default:
            cout<<"Invalid Selection"<<endl;
        }
    }
    return 0;
}

void ShowMenu(void)
{
    cout<<"-----Menu-----"<<endl;
    cout<<"1. Create Account"<<endl;
    cout<<"2. Deposit"<<endl;
    cout<<"3. Withdraw"<<endl;
    cout<<"4. Account Information"<<endl;
    cout<<"5. Quit"<<endl;
}

void CreateAccount(void)
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

void DepositMoney(void)
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

void WithdrawMoney(void)
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

void ShowAllInfo(void)
{
    for(int i=0; i<accNum; i++)
    {
        accArr[i]->ShowAccInfo();
        cout<<endl;
    }
}
