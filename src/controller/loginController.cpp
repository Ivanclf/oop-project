/**
 * @file loginController.cpp
 * @brief 登录控制器模块
 * @details 实现了用户登录、注册和退出系统的主要功能
 */

#include "../../include/header.hpp"
extern UserList *user_list;  // 用户列表指针
using namespace std;

// 函数前向声明
void loginUser();    // 用户登录函数
User registerUser(); // 用户注册函数

/**
 * @brief 登录控制器主函数
 * @return int 程序退出状态码
 * @details 提供系统的主入口界面，包括：
 * 1. 用户注册
 * 2. 用户登录
 * 3. 退出系统
 * 
 * 根据用户选择执行相应操作，并在登录成功后根据用户角色
 * 进入不同的控制界面（管理员/顾客）
 */
int loginController()
{
    int choice;
    while (true)
    {
        // 显示主菜单
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;

        User user;
        switch (choice)
        {
        case 1:  // 用户注册
            user = registerUser();
            if(user.getUsername().empty())  // 注册失败
                break;
            else if (user.getRole() == admin)  // 管理员注册成功
                adminController(user);
            else  // 顾客注册成功
                customerController(user);
            break;
        case 2:  // 用户登录
            loginUser();
            break;
        case 3:  // 退出系统
            cout << "Exiting program. Goodbye!\n";
            exit(0);
        default:  // 无效选择
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

/**
 * @brief 用户登录函数
 * @details 处理用户登录流程：
 * 1. 获取用户输入的用户名和密码
 * 2. 验证用户是否存在
 * 3. 验证密码是否正确
 * 4. 根据用户角色进入相应的控制界面
 */
void loginUser()
{
    string username, password;
    // 获取用户输入
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // 查找用户
    auto users = user_list->findUserByUsername(username);
    if (users.empty())
    {
        cout << "User not found. Please register first.\n";
        return;
    }

    // 验证密码
    User *userPtr = users.back();
    if (!userPtr->getUsername().empty() && userPtr->getPassword() == password)
    {
        // 登录成功，显示欢迎信息
        cout << "Login successful! Welcome, " 
             << (userPtr->getRole() == admin ? "Admin" : "Customer") 
             << " " << userPtr->getUsername() << ".\n";
        
        // 根据角色进入相应的控制界面
        userPtr->getRole() == admin ? adminController(*userPtr) : customerController(*userPtr);
        return;
    }
    else
        cout << "Incorrect username or password. Please try again.\n";
}

/**
 * @brief 用户注册函数
 * @return User 返回注册成功的用户对象，注册失败返回空用户
 * @details 处理用户注册流程：
 * 1. 获取用户输入的用户名、密码和角色
 * 2. 验证角色是否有效
 * 3. 检查用户名是否已存在
 * 4. 创建新用户并添加到用户列表
 */
User registerUser()
{
    string username, password;
    int role;
    
    // 获取用户输入
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter role (0 for admin/1 for customer): ";
    cin >> role;

    // 验证角色
    if (role != 0 && role != 1)
    {
        cout << "Invalid role. Please choose 'admin' or 'customer'.\n";
        return {};  // 返回空用户
    }

    // 检查用户名是否已存在
    if (!user_list->findUserByUsername(username).empty())
    {
        cout << "Username already exists. Please try again.\n";
        return {};  // 返回空用户
    }

    // 创建新用户并添加到用户列表
    User user = User(username, password, static_cast<Role>(role));
    user_list->addUser(user);
    cout << "Registration successful!\n";
    return user;
}