/**
 * @file adminController.cpp
 * @brief 管理员控制器模块
 * @details 实现了系统管理员界面的主要功能，包括：
 * 1. 用户管理（查看、更新用户信息）
 * 2. 商品管理（添加、更新、删除、查询商品）
 * 3. 订单管理（查看和修改订单状态）
 * 4. 折扣管理（商品折扣和用户折扣设置）
 * 5. 系统维护（密码修改等）
 */

#include "../../include/header.hpp"

extern UserList *user_list;  // 用户列表指针
using namespace std;

/**
 * @brief 管理员控制器主函数
 * @param user 当前登录的管理员用户对象
 * @details 提供管理员用户的主界面，包括以下功能：
 * 1. 退出系统
 * 2. 修改密码
 * 3. 用户管理
 *    - 查看所有用户
 *    - 更新用户信息
 * 4. 商品管理
 *    - 查看所有商品
 *    - 添加新商品
 *    - 更新商品信息
 *    - 删除商品
 *    - 搜索商品
 * 5. 订单管理
 *    - 管理用户订单状态
 *    - 修改订单状态
 * 6. 折扣管理
 *    - 修改商品折扣
 *    - 修改用户折扣
 * 
 * 通过循环显示菜单并处理用户选择，直到用户选择退出
 */
void adminController(User &user)
{
    int choice;
    while (true)
    {
        // 显示管理员功能菜单
        cout << "\n0. Exit"                    // 退出系统
             << "\n1. Change password"         // 修改密码
             << "\n2. List all users"          // 查看所有用户
             << "\n3. Update a user's data"    // 更新用户信息
             << "\n4. List all goods"          // 查看所有商品
             << "\n5. Add a new goods"         // 添加新商品
             << "\n6. Update information of a goods"  // 更新商品信息
             << "\n7. Delete a kind of goods"  // 删除商品
             << "\n8. Find goods"              // 搜索商品
             << "\n9. Manage user order status"  // 管理用户订单状态
             << "\n10. Change order status"    // 修改订单状态
             << "\n11. Change goods discount"  // 修改商品折扣
             << "\n12. Change user discount"   // 修改用户折扣
             << "\nChoose an option that you want to perform:\t";
        cin >> choice;

        // 根据用户选择执行相应功能
        switch (choice)
        {
        case 0:  // 退出系统
            cout << "have a nice day~\n";
            loginController();  // 返回登录界面
            break;
        case 1:  // 修改密码
            changePassword(user);
            break;
        case 2:  // 查看所有用户
            listAllUsers();
            break;
        case 3:  // 更新用户信息
            updateUser();
            break;
        case 4:  // 查看所有商品
            listAllGoods(user);
            break;
        case 5:  // 添加新商品
            addNewGoods();
            break;
        case 6:  // 更新商品信息
            updateGoods();
            break;
        case 7:  // 删除商品
            deleteGoods();
            break;
        case 8:  // 搜索商品
            searchGoods();
            break;
        case 9:  // 管理用户订单状态
            manageUserOrders();
            break;
        case 10:  // 修改订单状态
            change_Order_Status();
            break;
        case 11:  // 修改商品折扣
            changeGoodsDiscount();
            break;
        case 12:  // 修改用户折扣
            changeUserDiscount();
            break;
        default:  // 无效选择
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}