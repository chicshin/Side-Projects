#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN=20;

//declare functions
void ShowMenu(void);
void CreateAccount(void);
void DepositMoney(void);
void WithdrawMoney(void);
void ShowAllAccInfo(void);

enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

typedef struct
{
    int accID;
    int balance;
    char cusName[NAME_LEN];
} Account;

Account accArr[100];
int accNum=0;    //number of accounts

int main(void)
{
    int choice;

    while(1)
    {
        ShowMenu();
        cout<<"Select: ";
        cin>>choice;
        cout<<endl;

        switch(choice)
        {
            case MAKE:
                CreateAccount();
                break;
            case DEPOSIT:
                DepositMoney();
                break;
            case WITHDRAW:
                WithdrawMoney();
                break;
            case INQUIRE:
                ShowAllAccInfo();
                break;
            case EXIT:
                return 0;
            default:
                cout<<"Illegal selection.."<<endl;
        }
    }
    return 0;
}

void ShowMenu(void)
{
    cout<<"-----MENU-----"<<endl;
    cout<<"1. Create Account"<<endl;
    cout<<"2. Deposit Money"<<endl;
    cout<<"3. Withdraw Money"<<endl;
    cout<<"4. Account Information"<<endl;
    cout<<"5. Exit"<<endl;
}

void CreateAccount(void)
{
    int id;
    char name[NAME_LEN];
    int balance;

    cout<<"Create"<<endl;
    cout<<"Account ID: "; cin>>id;
    cout<<"Name: "; cin>>name;
    cout<<"Balance: "; cin>>balance;
    cout<<endl;

    accArr[accNum].accID=id;
    accArr[accNum].balance=balance;
    strcpy(accArr[accNum].cusName, name);
    accNum++;
}

void DepositMoney(void)
{
    int money;
    int id;
    cout<<"Deposit"<<endl;
    cout<<"Account ID: "; cin>>id;
    cout<<"Amount of Money: "; cin>>money;

    for (int i=0; i<accNum; i++)
    {
        if(accArr[i].accID==id)
        {
            accArr[i].balance+=money;
            cout<<"Depoist Completed"<<endl;
            return;
        }
    }
    cout<<"Invalid ID"<<endl<<endl;
}

void WithdrawMoney(void)
{
    int money;
    int id;
    cout<<"Withdrawl"<<endl;
    cout<<"Account ID: "; cin>>id;
    cout<<"Amount of Money: "; cin>>money;

    for (int i=0; i<accNum; i++)
    {
        if(accArr[i].accID==id)
        {
            if(accArr[i].balance<money)
            {
                cout<<"Insufficient balance"<<endl;
                return;
            }

            accArr[i].balance-=money;
            cout<<"Withdrawl Completed"<<endl;
            return;
        }
    }
    cout<<"Invalid ID"<<endl<<endl;
}

void ShowAllAccInfo(void)
{
    for(int i=0; i<accNum; i++)
    {
        cout<<"Account ID: "<<accArr[i].accID<<endl;
        cout<<"Name: "<<accArr[i].cusName<<endl;
        cout<<"Balance: "<<accArr[i].balance<<endl<<endl;
    }
}
