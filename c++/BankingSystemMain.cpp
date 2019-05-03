#include "BankingCommonDec1.h"
#include "AccountHandler.h"

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
