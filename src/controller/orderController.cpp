#include "../../include/header.hpp"
using namespace std;

void orderController(vector<Order> &orders)
{
    int choice;
    while (true)
    {
        if (orders.empty())
        {
            cout << "\nNo orders available.\n";
            return;
        }

        cout << "\nList of all orders:\n";
        for (size_t i = 0; i < orders.size(); ++i)
        {
            cout << i + 1 << ". Order with " << orders[i].getItems().size() << " items.\n";
        }

        cout << "\nChoose an option:\n"
             << "0. Exit\n"
             << "1. List orders by status\n"
             << "2. Delete an order (only unpayed or checked orders)\n"
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
            cout << "\nChoose a status to filter orders:\n"
                 << "1. Undefined\n"
                 << "2. Unpayed\n"
                 << "3. Not Delivered\n"
                 << "4. Delivered\n"
                 << "5. Checked\n"
                 << "Enter your choice: ";
            cin >> statusChoice;

            order_status filterStatus = static_cast<order_status>(statusChoice - 1);
            cout << "\nOrders with status " << statusChoice << ":\n";
            for (size_t i = 0; i < orders.size(); ++i)
            {
                cout << "Order " << i + 1 << ":\n";
                orders[i].printItemsByStatus(filterStatus);
            }
            break;
        }

        case 2:
        {
            int orderIndex;
            cout << "\nEnter the order number to delete: ";
            cin >> orderIndex;

            if (orderIndex <= 0 || orderIndex > static_cast<int>(orders.size()))
            {
                cout << "Invalid order number.\n";
                break;
            }

            Order &order = orders[orderIndex - 1];
            if (order.getItemStatus("") == unpayed || order.getItemStatus("") == checked)
            {
                orders.erase(orders.begin() + (orderIndex - 1));
                cout << "Order deleted successfully.\n";
            }
            else
            {
                cout << "Only unpayed or checked orders can be deleted.\n";
            }
            break;
        }

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void changeOrderStatus(vector<Order> &orders)
{
    int orderIndex, statusChoice;
    cout << "\nEnter the order number to change status: ";
    cin >> orderIndex;

    if (orderIndex <= 0 || orderIndex > static_cast<int>(orders.size()))
    {
        cout << "Invalid order number.\n";
        return;
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
    orders[orderIndex - 1].setItemStatus("", newStatus);
    cout << "Order status updated successfully.\n";
}