/**
 * @file userController.cpp
 * @brief 用户控制器模块
 * @details 实现了用户管理的主要功能，包括：
 * 1. 用户信息管理（密码修改、信息更新）
 * 2. 用户列表管理（查看、更新用户信息）
 * 3. 订单状态管理（修改订单状态）
 * 4. 折扣管理（计算折扣、修改折扣）
 */

#include "../../include/header.hpp"
using namespace std;

// 外部全局变量声明
extern UserList *user_list;    // 用户列表指针
extern GoodsList *goods_list;  // 商品列表指针

/**
 * @brief 修改用户密码
 * @param user 要修改密码的用户对象
 * @details 处理修改用户密码的流程：
 * 1. 获取新密码
 * 2. 更新用户密码
 * 3. 保存更改到文件
 */
void changePassword(User &user)
{
    string newPassword;
    cout << "Enter new password: ";
    cin >> newPassword;
    user.setPassword(newPassword);
    writeToFile();  // 保存更改到文件
    cout << "Password updated successfully.\n";
}

/**
 * @brief 显示所有用户列表
 * @details 遍历并显示系统中所有用户的信息
 */
void listAllUsers() { user_list->iterateUsers(); }

/**
 * @brief 更新用户信息
 * @details 处理更新用户信息的流程：
 * 1. 查找要更新的用户
 * 2. 获取新的用户信息
 * 3. 更新用户信息
 * 4. 保存更改到文件
 */
void updateUser()
{
    string usernameOld, usernameNew, password;
    User *update;
USERNAME_INPUT:
    // 获取要更新的用户名
    cout << "Enter the username of the customer to update: ";
    cin >> usernameOld;
    if (user_list->findUserByUsername(usernameOld).empty())
    {
        cout << "\n the user does not exist!";
        goto USERNAME_INPUT;
    }

    // 获取新的用户信息
    cout << "\n enter new username: ";
    cin >> usernameNew;
    cout << "\n enter new password: ";
    cin >> password;

    // 创建新用户对象并更新
    update = new User(usernameNew, password, customer);
    if (user_list->updateUser(usernameOld, *update)) {
        writeToFile();  // 保存更改到文件
    }
    delete update;  // 释放内存
}

/**
 * @brief 修改订单状态
 * @details 处理修改订单状态的流程：
 * 1. 查找指定用户
 * 2. 显示用户订单
 * 3. 修改指定订单的状态
 * 4. 保存更改到文件
 */
void change_Order_Status()
{
    string userName, itemName;
    cout << "Input the username: ";
    cin >> userName;
    getchar();
    
    // 查找用户
    auto users = user_list->findUserByUsername(userName);
    if (users.empty())
    {
        cout << "User not found.\n";
        return;
    }

    // 获取用户订单并显示
    User &targetUser = user_list->getUserList().at(userName);
    Order &orders = targetUser.getUserOrder();
    cout << "User's orders:\n";
    orders.iterateGoods();

    // 修改订单状态
    cout << "Input the item name you want to change status: ";
    cin >> itemName;
    cout << "Input new status (0-undefined, 1-unpayed, 2-not_deliverd, 3-deliverd, 4-checked): ";
    int statusInt;
    cin >> statusInt;
    if (orders.setItemStatus(itemName, static_cast<order_status>(statusInt))) {
        writeToFile();  // 保存更改到文件
        cout << "Order status updated.\n";
    }
    else
        cout << "Failed to update order status. Check item name.\n";
}

/**
 * @brief 管理用户订单
 * @details 处理管理用户订单的流程：
 * 1. 查找指定用户
 * 2. 显示用户订单
 * 3. 修改指定订单的状态
 * 4. 保存更改到文件
 */
void manageUserOrders()
{
    string uname;
    cout << "Input the username: ";
    cin >> uname;
    
    // 查找用户
    auto users = user_list->findUserByUsername(uname);
    if (users.empty())
    {
        cout << "User not found.\n";
        return;
    }

    // 获取用户订单并显示
    User &targetUser = user_list->getUserList().at(uname);
    Order &orders = targetUser.getUserOrder();
    cout << "User's orders:\n";
    orders.iterateGoods();

    // 修改订单状态
    string itemName;
    cout << "Input the item name you want to change status: ";
    cin >> itemName;
    cout << "Input new status (0-undefined, 1-unpayed, 2-not_deliverd, 3-deliverd, 4-checked): ";
    int statusInt;
    cin >> statusInt;
    if (orders.setItemStatus(itemName, static_cast<order_status>(statusInt))) {
        writeToFile();  // 保存更改到文件
        cout << "Order status updated.\n";
    }
    else
        cout << "Failed to update order status. Check item name.\n";
}

/**
 * @brief 计算用户折扣
 * @param user 要计算折扣的用户对象
 * @details 计算用户购物车中商品的折扣：
 * 1. 计算商品原价和折扣价
 * 2. 应用商品折扣
 * 3. 应用用户折扣
 * 4. 显示折扣信息
 */
void computeDiscount(User &user)
{
    int total = 0, quantity = 0, original = 0;
    
    // 计算商品总价和折扣
    for (auto &it : user.getCart().getItems())
    {
        original += it.goods->getPrice() * it.quantity;
        if (it.goods->getIsDiscounted())
        {
            total += it.goods->getDiscountedPrice() * it.quantity;
            quantity += it.quantity;
            cout << "You have enjoy discount on the goods: " << it.goods->getName() 
                 << " for total " << (it.goods->getPrice() - it.goods->getDiscountedPrice()) * it.quantity << "\n";
        }
        else
        {
            total += it.goods->getPrice() * it.quantity;
            quantity += it.quantity;
        }
    }

    // 应用用户折扣
    for (auto &it : user.getDiscountList())
    {
        if (total >= it.second && total >= it.first) {
            total -= it.second;
            break;
        }
    }

    // 显示折扣信息
    cout << "total quantity: " << quantity << ", total price: " << total << "\n";
    cout << "original price: " << original << ", total discount: " << original - total << "\n";
}

/**
 * @brief 修改商品折扣
 * @details 处理修改商品折扣的流程：
 * 1. 查找指定商品
 * 2. 设置新的折扣率
 * 3. 保存更改到文件
 */
void changeGoodsDiscount()
{
    string name;
    cout << "Enter the name of goods to modify discount: ";
    cin >> name;
    
    // 查找商品
    auto goods = goods_list->findGoodsByName(name);
    if (goods.empty()) {
        cout << "Goods not found\n";
        return;
    }

    // 设置新的折扣率
    double discount;
    cout << "Enter new discount rate (0.1-1.0): ";
    cin >> discount;
    
    if (discount < 0.1 || discount > 1.0) {
        cout << "Invalid discount rate\n";
        return;
    }

    goods[0]->setDiscountScale(discount);
    writeToFile();  // 保存更改到文件
    cout << "Goods discount updated successfully\n";
}

/**
 * @brief 修改用户折扣
 * @details 处理修改用户折扣的流程：
 * 1. 查找指定用户
 * 2. 显示当前折扣信息
 * 3. 添加或删除折扣
 * 4. 保存更改到文件
 */
void changeUserDiscount()
{
    string username;
    cout << "Enter username to modify discount: ";
    cin >> username;

    // 查找用户
    auto users = user_list->findUserByUsername(username);
    if (users.empty()) {
        cout << "User not found\n";
        return;
    }

    // 显示当前折扣信息
    User* user = users[0];
    cout << "Current user discounts:\n";
    for (auto &discount : user->getDiscountList()) {
        cout << "Spend " << discount.first << " get " << discount.second << "% off\n";
    }

    // 选择操作类型
    int choice;
    cout << "\n1. Add discount\n2. Remove discount\nPlease choose: ";
    cin >> choice;

    if (choice == 1) {  // 添加折扣
        int discount, limit;
        cout << "Enter discount percentage: ";
        cin >> discount;
        cout << "Enter spending limit: ";
        cin >> limit;
        
        if (user->addDiscount(discount, limit)) {
            writeToFile();  // 保存更改到文件
            cout << "Discount added successfully\n";
        } else {
            cout << "This discount already exists\n";
        }
    } else if (choice == 2) {  // 删除折扣
        int discount, limit;
        cout << "Enter discount percentage to remove: ";
        cin >> discount;
        cout << "Enter spending limit to remove: ";
        cin >> limit;
        
        if (user->deleteDiscount(discount, limit)) {
            writeToFile();  // 保存更改到文件
            cout << "Discount removed successfully\n";
        } else {
            cout << "Discount not found\n";
        }
    } else {
        cout << "Invalid choice\n";
    }
}

/**
 * @brief 显示用户折扣信息
 * @param user 要显示折扣信息的用户对象
 * @details 遍历并显示用户的所有折扣信息
 */
void iterateDiscount(User &user)
{
    auto list = user.getDiscountList();
    if(list.empty())
    {
        cout << "\nNo discount available";
        return;
    }
    for(auto &it : list)
    {
        cout << "\nTotal reach " << it.first << " you will have " << it.second << " discount";
    }
}