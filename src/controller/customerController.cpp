/**
 * @file customerController.cpp
 * @brief 顾客控制器模块
 * @details 实现了顾客用户界面的主要功能，包括：
 * 1. 密码管理
 * 2. 商品浏览和搜索
 * 3. 购物车操作
 * 4. 订单管理
 * 5. 折扣计算和查看
 */

#include "../../include/header.hpp"
using namespace std;

/**
 * @brief 顾客控制器主函数
 * @param user 当前登录的顾客用户对象
 * @details 提供顾客用户的主界面，包括以下功能：
 * 1. 退出系统
 * 2. 修改密码
 * 3. 浏览所有商品
 * 4. 搜索商品
 * 5. 打开购物车
 * 6. 查看订单
 * 7. 计算折扣
 * 8. 显示折扣信息
 * 
 * 通过循环显示菜单并处理用户选择，直到用户选择退出
 */
void customerController(User &user)
{
    int choice;
    while (true)
    {
        // 显示顾客功能菜单
        cout << "\n0. Exit"                    // 退出系统
             << "\n1. Change password"         // 修改密码
             << "\n2. List all goods on this screen"  // 浏览所有商品
             << "\n3. Search goods"           // 搜索商品
             << "\n4. Open your cart"         // 打开购物车
             << "\n5. Open your order"        // 查看订单
             << "\n6. Compute discount"       // 计算折扣
             << "\n7. Show your discount"     // 显示折扣信息
             << "\nChoose an option that you wanna do:\t";
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
        case 2:  // 浏览所有商品
            listAllGoods(user);
            break;
        case 3:  // 搜索商品
            searchGoods();
            break;
        case 4:  // 购物车操作
            cartController(user.getCart(), user.getUserOrder());
            break;
        case 5:  // 订单管理
            orderController(user.getUserOrder());
            break;
        case 6:  // 计算折扣
            computeDiscount(user);
            break;
        case 7:  // 显示折扣信息
            iterateDiscount(user);
            break;
        default:  // 无效选择
            cout << "you have pressed a wrong number, please press again!\n";
            continue;
        }
    }
}