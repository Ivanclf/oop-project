#include "../../include/header.hpp"
using namespace std;

extern UserList *user_list;

void changePassword(User &user)
{
    string newPassword;
    cout << "Enter new password: ";
    cin >> newPassword;
    user.setPassword(newPassword);
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

void change_Order_Status()
{
    string userName, itemName;
    cout << "Input the username: ";
    cin >> userName;
    auto users = user_list->findUserByUsername(userName);
    if (users.empty())
    {
        cout << "User not found.\n";
        return;
    }
    User &targetUser = user_list->getUserList().at(userName);
    Order &orders = targetUser.getUserOrder();
    cout << "User's orders:\n";
    orders.iterateGoods();
    cout << "Input the item name you want to change status: ";
    cin >> itemName;
    cout << "Input new status (0-undefined, 1-unpayed, 2-not_deliverd, 3-deliverd, 4-checked): ";
    int statusInt;
    cin >> statusInt;
    if (orders.setItemStatus(itemName, static_cast<order_status>(statusInt)))
        cout << "Order status updated.\n";
    else
        cout << "Failed to update order status. Check item name.\n";
}

void manageUserOrders()
{
    string uname;
    cout << "Input the username: ";
    cin >> uname;
    auto users = user_list->findUserByUsername(uname);
    if (users.empty())
    {
        cout << "User not found.\n";
        return;
    }
    User &targetUser = user_list->getUserList().at(uname);
    Order &orders = targetUser.getUserOrder();
    cout << "User's orders:\n";
    orders.iterateGoods();
    string itemName;
    cout << "Input the item name you want to change status: ";
    cin >> itemName;
    cout << "Input new status (0-undefined, 1-unpayed, 2-not_deliverd, 3-deliverd, 4-checked): ";
    int statusInt;
    cin >> statusInt;
    if (orders.setItemStatus(itemName, static_cast<order_status>(statusInt)))
        cout << "Order status updated.\n";
    else
        cout << "Failed to update order status. Check item name.\n";
}