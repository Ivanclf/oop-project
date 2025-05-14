#include "../../include/header.hpp"
using namespace std;

void customerController(User &user)
{
    int choice;
    while (true)
    {
        cout << "\n0. Exit"
             << "\n1. Change password"
             << "\n2. List all goods on this screen"
             << "\n3. Search goods"
             << "\n4. Open your cart"
             << "\nChoose an option that you wanna do:\t";
        cin >> choice;
        auto cart = user.getCart();
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
            listAllGoods(user);
            break;
        case 3:
            searchGoods();
            break;
        case 4:
            cartController(cart);
            break;
        default:
            cout << "you have pressed a wrong number, please press again!\n";
            continue;
        }
    }
}