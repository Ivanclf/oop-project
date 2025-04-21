#include "../../include/header.hpp"
using namespace std;

void customerController(User *user)
{
    int choice;
    while (true)
    {
        cout << "0. Exit" << "\n"
             << "1. Change password" << "\n"
             << "2. List all goods on this screen" << "\n"
             << "Choose an option that you wanna do:\t";
        cin >> choice;
        switch (choice)
        {
        case 0:
        {
            cout << "hava a nice day~\n";
            loginController();
        }
        case 1:
        {
            string newPassword;
            cout << "Enter your new password: ";
            cin >> newPassword;
            user->setPassword(newPassword);
            cout << "Password changed successfully!" << endl;
            break;
        }
        case 2:
        {
            
        }
        }
    }
}