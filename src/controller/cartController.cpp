#include "../../include/header.hpp"
using namespace std;

void cartController(cart userCart)
{
    int choice, option = 0, quantity;
    while(true)
    {
        cout << "\nThis is your cart. What you have chosen is on the list:\n";
        userCart.iterateGoods();
        cout << "\n0. Exit"
        << "\n1. Delete a item"
        << "\n2. Change the quantity of an item"
        << "\nChoose an option that you wanna do:\t";
        cin >> choice;
        switch (choice)
        {
        case 0:
            cout << "ByeBye!~\n";
            return;
            break;
        case 1:
            cout << "Input the order that you wanna delete: \t";
            cin >> option;
            if(userCart.deleteItem(option))
                cout << "you have delete a item successfully\n";
            else
                cout << "delete failed! check if you have inputted right order\n";
            break;
        case 2:
            cout << "Input the order that you wanna change: \t";
            cin >> option;
            if (option <= 0 || option > userCart.getSize())
            {
                cout << "change failed! check if you inputted right order\n";
                break;
            }
            cout << "Input the new quantity:\t";
            cin >> quantity;

            if(userCart.changeQuantity(userCart.getItem(option), quantity))
            {
                cout << "you have change the quantity of a item successfully\n";
            }
            else
                cout << "change failed! check if the storage is enough!";
            break;
        default:
        cout << "you have pressed a wrong number, please press again!\n";
        break;
        }
    }
}