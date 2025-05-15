#include "../../include/header.hpp"

extern UserList *user_list;
using namespace std;

void adminController(User &user)
{
    int choice;
    while (true)
    {
        cout << "\n0. Exit"
             << "\n1. Change password"
             << "\n2. List all users"
             << "\n3. Update a user's data"
             << "\n4. List all goods"
             << "\n5. Add a new goods"
             << "\n6. Update information of a goods"
             << "\n7. Delete a kind of goods"
             << "\n8. Find goods"
             << "\n9. Manage user order status"
             << "\nChoose an option that you want to perform:\t";
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
            listAllUsers();
            break;
        case 3:
            updateUser();
            break;
        case 4:
            listAllGoods(user);
            break;
        case 5:
            addNewGoods();
            break;
        case 6:
            updateGoods();
            break;
        case 7:
            deleteGoods();
            break;
        case 8:
            searchGoods();
            break;
        case 9:
        {
            string uname;
            cout << "Input the username: ";
            cin >> uname;
            auto users = user_list->findUserByUsername(uname);
            if (users.empty()) {
                cout << "User not found.\n";
                break;
            }
            User &targetUser = user_list->getUserList().at(uname);
            Order &orders = targetUser.getUserOrder();
            cout << "User's orders:\n";
            orders.printAllItems();
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
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}