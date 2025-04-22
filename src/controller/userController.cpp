#include "../../include/header.hpp"
using namespace std;

extern UserList *user_list;

void changePassword(User *user)
{
    string newPassword;
    cout << "Enter new password: ";
    cin >> newPassword;
    user->setPassword(newPassword);
    cout << "Password updated successfully.\n";
}

void listAllUsers() { user_list->iterateUsers(); }

void updateUser()
{
    string usernameOld, usernameNew, password;
    User *update;
USERNAME_INPUT:
    cout << "Enter the username of the customer to update: ";
    cin >> usernameOld;
    if (user_list->findUserByUsername(usernameOld).empty())
    {
        cout << "\n the user does not exist!";
        goto USERNAME_INPUT;
    }
    cout << "\n enter new username: ";
    cin >> usernameNew;
    cout << "\n enter new password: ";
    cin >> password;
    update = new User(usernameNew, password, customer);
    user_list->updateUser(usernameOld, *update);
}