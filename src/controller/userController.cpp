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
    getchar();
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

void computeDiscount(User &user)
{
    int total = 0, quantity = 0, original = 0;
    for (auto &it : user.getCart().getItems())
    {
        if (it.goods.getIsDiscounted())
        {
            total += it.goods.getDiscountedPrice() * it.quantity;
            quantity += it.quantity;
            cout << "You have enjoy discount on the goods: " << it.goods.getName() << " for total " << (it.goods.getPrice() - it.goods.getDiscountedPrice()) * it.quantity << "\n";
        }
        else
        {
            total += it.goods.getPrice() * it.quantity;
            quantity += it.quantity;
        }
    }
    for (auto &it : user.getDiscountList())
    {
        if (it.second >= total && (original == 0 || it.second < original))
        {
            original = it.second;
            total = total * (1 - it.first / 100.0);
        }
    }
    cout << "total quantity: " << quantity << ", total price: " << total << "\n";
    cout << "original price: " << original << ", total discount: " << original - total << "\n";
}

void changeGoodsDiscount()
{
    string name;
    cout << "Enter the name of goods to modify discount: ";
    cin >> name;
    
    auto goods = goods_list->findGoodsByName(name);
    if (goods.empty()) {
        cout << "Goods not found\n";
        return;
    }

    double discount;
    cout << "Enter new discount rate (0.1-1.0): ";
    cin >> discount;
    
    if (discount < 0.1 || discount > 1.0) {
        cout << "Invalid discount rate\n";
        return;
    }

    goods[0]->setDiscount(discount);
    cout << "Goods discount updated successfully\n";
}

void changeUserDiscount()
{
    string username;
    cout << "Enter username to modify discount: ";
    cin >> username;

    auto users = user_list->findUserByUsername(username);
    if (users.empty()) {
        cout << "User not found\n";
        return;
    }

    User* user = users[0];
    cout << "Current user discounts:\n";
    for (auto &discount : user->getDiscountList()) {
        cout << "Spend " << discount.second << " get " << discount.first << "% off\n";
    }

    int choice;
    cout << "\n1. Add discount\n2. Remove discount\nPlease choose: ";
    cin >> choice;

    if (choice == 1) {
        int discount, limit;
        cout << "Enter discount percentage: ";
        cin >> discount;
        cout << "Enter spending limit: ";
        cin >> limit;
        
        if (user->addDiscount(discount, limit)) {
            cout << "Discount added successfully\n";
        } else {
            cout << "This discount already exists\n";
        }
    } else if (choice == 2) {
        int discount, limit;
        cout << "Enter discount percentage to remove: ";
        cin >> discount;
        cout << "Enter spending limit to remove: ";
        cin >> limit;
        
        if (user->deleteDiscount(discount, limit)) {
            cout << "Discount removed successfully\n";
        } else {
            cout << "Discount not found\n";
        }
    } else {
        cout << "Invalid choice\n";
    }
}

