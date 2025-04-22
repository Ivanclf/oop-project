#include "../../include/header.hpp"
using namespace std;

void customerController(User *user)
{
    int choice;
    while (true)
    {
        cout << "\n0. Exit"
             << "\n1. Change password"
             << "\n2. List all goods on this screen"
             << "\n3. Search goods"
             << "\nChoose an option that you wanna do:\t";
        cin >> choice;
        switch (choice)
        {
        case 0:
            cout << "hava a nice day~\n";
            loginController();
            break;
        case 1:
            changePassword(user);
            break;
        case 2:
            listAllGoods();
            break;
        default:
        {
            cout << "you have pressed a wrong number, please press again!\n";
            continue;
        }
        }
    }
}