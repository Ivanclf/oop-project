#include "../../include/header.hpp"

extern UserList *user_list;
using namespace std;

void adminController(User *user)
{
    int choice;
    while (true)
    {
        cout << "\n0. exit\n1. Change password\n2. List all users\n3. Update a user's data\nChoose an option that you wanna do:\t";
        cin >> choice;
        switch (choice)
        {
        case 0:
        {
            cout << "have a nice day~\n";
            loginController();
        }
        case 1:
        {
            string newPassword;
            cout << "Enter new password: ";
            cin >> newPassword;
            user->setPassword(newPassword);
            cout << "Password updated successfully.\n";
        }
        break;
        case 2:
        {
            cout << "List of all customer-level users:\n";
            user_list->iterateUsers();
        }
        break;
        case 3:
        {
            string usernameOld, usernameNew, password;
            User *update;
            cout << "Enter the username of the customer to update: ";
            cin >> usernameOld;
            if (user_list->findUserByUsername(usernameOld) == nullptr)
            {
                cout << "\n the user does not exist!";
                break;
            }
            cout << "\n enter new username: ";
            cin >> usernameNew;
            cout << "\n enter new password: ";
            cin >> password;
            update = new User(usernameNew, password, customer);
            user_list->updateUser(usernameOld, *update);
        }
        break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}