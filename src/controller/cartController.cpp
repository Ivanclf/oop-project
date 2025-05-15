#include "../../include/header.hpp"
using namespace std;

extern GoodsList *goods_list;

void cartController(Cart &userCart, Order &orders)
{
    int choice, option = 0, quantity = 0;
    bool temp = false;
    while (true)
    {
        cout << "\nThis is your cart. What you have chosen is on the list:\n";
        userCart.iterateGoods();
        cout << "\n\n0. Exit"
             << "\n1. Delete a item"
             << "\n2. Change the quantity of an item"
             << "\n3. Add all items in cart to order"
             << "\n4. Add a single item in cart to order"
             << "\nChoose an option that you wanna do:\t";
        cin >> choice;
        auto item = &(userCart.getItem(option));
        switch (choice)
        {
        case 0:
            cout << "ByeBye!~\n";
            return;
        case 1:
            cout << "Input the order that you wanna delete: \t";
            cin >> option;
            if (userCart.deleteItem(option))
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
            if (!quantity)
            {
                temp = userCart.deleteItem(option);
                if (temp)
                    cout << "you have delete a item successfully\n";
                else
                    cout << "delete failed! check if you have inputted right order\n";
                break;
            }
            item = &(userCart.getItem(option));
            cout << item->item.getStorage() << '\n';
            if (userCart.changeQuantity(*item, quantity))
            {
                cout << "you have change the quantity of a item successfully\n";
            }
            else
                cout << "change failed! check if the storage is enough!";
            break;
        case 3: 
            if (userCart.getSize() == 0) {
                cout << "Cart is empty, nothing to add.\n";
                break;
            }
            orders.addItem(userCart.getItems()); 
            cout << "All items in cart have been added to your order.\n";
            break;
        case 4: 
            cout << "Input the order number of the item to add to order: ";
            cin >> option;
            if (option <= 0 || option > userCart.getSize()) {
                cout << "Invalid order number.\n";
                break;
            }
            orders.addItem(userCart.getItem(option));
            cout << "Item has been added to your order.\n";
            break;
        default:
            cout << "you have pressed a wrong number, please press again!\n";
            break;
        }
    }
}

void addNew(Cart &userCart)
{
    string name;
    int quantity;
    vector<Goods> temp;
    while (true)
    {
        cout << "\nwhich one would you like to choose?"
             << "\n(input name and quantity of goods)"
             << "\nname: ";
        cin >> name;
        cout << "quantity: ";
        cin >> quantity;

        temp = goods_list->findGoodsByName(name);
        if (temp.empty() || quantity <= 0)
        {
            cout << "You have input wrong parameter(s)!";
            break;
        }
        else
        {
            Item newItem = *(new Item(*temp.begin(), quantity));
            userCart.addItem(newItem);
            cout << "\noperation succeed!";
            break;
        }
    }
}