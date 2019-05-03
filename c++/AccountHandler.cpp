#include "BankingCommonDec1.h"
#include "Account.h"
#include "AccountHandler.h"
#include "NormalAccount.h"
#include "HighCreditAccount.h"

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
