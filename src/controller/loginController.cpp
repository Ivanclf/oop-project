#include "../../include/header.hpp"
extern UserList *user_list;
using namespace std;

void loginUser();
User registerUser();

int loginController()
{
    int choice;
    while (true)
    {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;

        User user;
        switch (choice)
        {
        case 1:
            user = registerUser();
            if(user.getUsername().empty())
                break;
            else if (user.getRole() == admin)
                adminController(user);
            else
                customerController(user);
            break;
        case 2:
            loginUser();
            break;
        case 3:
            cout << "Exiting program. Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void loginUser()
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    auto users = user_list->findUserByUsername(username);
    if (users.empty())
    {
        cout << "User not found. Please register first.\n";
        return;
    }

    User user = users[0];
    if (!user.getUsername().empty() && user.getPassword() == password)
    {
        cout << "Login successful! Welcome, " << (user.getRole() == admin ? "Admin" : "Customer") << " " << user.getUsername() << ".\n";
        user.getRole() == admin ? adminController(user) : customerController(user);
    }
    else
        cout << "Incorrect username or password. Please try again.\n";
}

User registerUser()
{
    string username, password;
    int role;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter role (0 for admin/1 for customer): ";
    cin >> role;

    if (role != 0 && role != 1)
    {
        cout << "Invalid role. Please choose 'admin' or 'customer'.\n";
        return {};
    }

    if (!user_list->findUserByUsername(username).empty())
    {
        cout << "Username already exists. Please try again.\n";
        return {};
    }
    User user = User(username, password, static_cast<Role>(role));
    user_list->addUser(user);
    cout << "Registration successful!\n";
    return user;
}