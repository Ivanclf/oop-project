#include "../../include/header.hpp"
using namespace std;
extern GoodsList *goods_list;

void cartController(Cart &userCart, Order &order)
{
    int choice, quantity = 0;
    bool temp = false;
    string name;
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
        switch (choice)
        {
        case 0:
            cout << "ByeBye!~\n";
            return;
        case 1:
            cout << "Input the name of the item you want to delete: ";
            cin >> name;
            if (userCart.deleteItem(name))
                cout << "you have delete a item successfully\n";
            else
                cout << "delete failed! check if you have inputted right name\n";
            break;
        case 2:
            cout << "Input the name of the item you want to change: ";
            cin >> name;
            cout << "Input the new quantity:\t";
            cin >> quantity;
            if (!quantity)
            {
                temp = userCart.deleteItem(name);
                if (temp)
                    cout << "you have delete a item successfully\n";
                else
                    cout << "delete failed! check if you have inputted right name\n";
                break;
            }
            if (userCart.changeQuantity(name, quantity))
            {
                cout << "you have change the quantity of a item successfully\n";
            }
            else
                cout << "change failed! check if the storage is enough or name is correct!";
            break;
        case 3:
            if (userCart.getSize() == 0)
            {
                cout << "Cart is empty, nothing to add.\n";
                break;
            }
            for (auto &it : userCart.getItems())
                it.status = unpayed;
            
            for (auto &it : userCart.getItems())
            {
                if (it.goods)
                {
                    string gname = it.goods->getName();
                    order.addItem(gname, it.quantity, it.status);
                }
            }
            cout << "All items in cart have been added to your order.\n";
            userCart.getItems().clear();
            break;
        case 4:
            cout << "Input the name of the item to add to order: ";
            cin >> name;
            for (auto &it : userCart.getItems())
            {
                if (it.goods && it.goods->getName() == name)
                {
                    order.addItem(name, it.quantity, unpayed);
                    userCart.deleteItem(name);
                    cout << "Item has been added to your order.\n";
                    goto end_case4;
                }
            }
            cout << "Invalid item name.\n";
        end_case4:
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
    vector<Goods*> temp;
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
            userCart.addItem(name, quantity);
            cout << "\noperation succeed!";
            break;
        }
    }
}