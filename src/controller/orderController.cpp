#include "../../include/header.hpp"
using namespace std;
extern GoodsList *goods_list;

void orderController(Order &orders)
{
    int choice;
    while (true)
    {
        vector<Item> items = orders.getItems();
        if (items.empty())
        {
            cout << "\nNo items in your order.\n";
            return;
        }

        cout << "\nList of all items in your order:\n";
        for (size_t i = 0; i < items.size(); ++i)
        {
            cout << i + 1 << ". " << items[i].goods->getName()
                 << " | Quantity: " << items[i].quantity
                 << " | Status: " << items[i].status << endl;
        }

        cout << "\nChoose an option:\n"
             << "0. Exit\n"
             << "1. List items by status\n"
             << "2. Delete an item (only unpayed or checked)\n"
             << "3. Change item status\n"
             << "4. Change order status\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 0:
            cout << "Exiting order management.\n";
            return;

        case 1:
        {
            int statusChoice;
            cout << "\nChoose a status to filter items:\n"
                 << "1. Undefined\n"
                 << "2. Unpayed\n"
                 << "3. Not Delivered\n"
                 << "4. Delivered\n"
                 << "5. Checked\n"
                 << "Enter your choice: ";
            cin >> statusChoice;

            order_status filterStatus = static_cast<order_status>(statusChoice - 1);
            cout << "\nItems with status " << statusChoice << ":\n";
            orders.iterateGoodsByStatus(filterStatus);
            break;
        }

        case 2:
        {
            int itemIndex;
            cout << "\nEnter the item number to delete: ";
            cin >> itemIndex;

            if (itemIndex <= 0 || itemIndex > static_cast<int>(items.size()))
            {
                cout << "Invalid item number.\n";
                break;
            }

            string itemName = items[itemIndex - 1].goods ? items[itemIndex - 1].goods->getName() : "";
            order_status st = orders.getItemStatus(itemName);
            if (st == unpayed || st == checked)
            {
                if (orders.deleteItem(itemName))
                    cout << "Item deleted successfully.\n";
                else
                    cout << "Delete failed.\n";
            }
            else
            {
                cout << "Only unpayed or checked items can be deleted.\n";
            }
            break;
        }

        case 3:
        {
            int itemIndex, statusChoice;
            cout << "\nEnter the item number to change status: ";
            cin >> itemIndex;
            if (itemIndex <= 0 || itemIndex > static_cast<int>(items.size()))
            {
                cout << "Invalid item number.\n";
                break;
            }
            cout << "\nChoose a new status:\n"
                 << "1. Undefined\n"
                 << "2. Unpayed\n"
                 << "3. Not Delivered\n"
                 << "4. Delivered\n"
                 << "5. Checked\n"
                 << "Enter your choice: ";
            cin >> statusChoice;
            order_status newStatus = static_cast<order_status>(statusChoice - 1);
            string itemName = items[itemIndex - 1].goods ? items[itemIndex - 1].goods->getName() : "";
            if (orders.setItemStatus(itemName, newStatus))
                cout << "Item status updated successfully.\n";
            else
                cout << "Failed to update item status.\n";
            break;
        }

        case 4:
            changeOrderStatus(orders);
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void changeOrderStatus(Order &orders)
{
    string itemName;
    int statusChoice;
    cout << "\nEnter the name of the item to change status: ";
    cin >> itemName;

    cout << "\nChoose a new status:\n"
         << "1. Undefined\n"
         << "2. Unpayed\n"
         << "3. Not Delivered\n"
         << "4. Delivered\n"
         << "5. Checked\n"
         << "Enter your choice: ";
    cin >> statusChoice;

    order_status newStatus = static_cast<order_status>(statusChoice - 1);

    switch (newStatus)
    {
    case undefined:
    case unpayed:
    case not_delivered:
    case delivered:
    case checked:
        if (orders.setItemStatus(itemName, newStatus))
            cout << "Order status updated successfully.\n";
        else
            cout << "Failed to update order status. Item may not exist.\n";
        break;
    default:
        cout << "Invalid status choice.\n";
        break;
    }
}