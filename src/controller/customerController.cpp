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
             << "\n5. Open your order"
             << "\n6. Compute discount"
             << "\nChoose an option that you wanna do:\t";
        cin >> choice;
        switch (choice)
        {
        case 0:
            cout << "have a nice day~\n";
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
            cartController(user.getCart(), user.getUserOrder());
            break;
        case 5:
            orderController(user.getUserOrder());
            break;
        case 6:
            computeDiscount(user);
            break;
        default:
            cout << "you have pressed a wrong number, please press again!\n";
            continue;
        }
    }
}