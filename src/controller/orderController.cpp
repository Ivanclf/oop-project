/**
 * @file orderController.cpp
 * @brief 订单控制器模块
 * @details 实现了订单管理的主要功能，包括：
 * 1. 订单查看和列表显示
 * 2. 订单状态管理
 * 3. 订单项目删除
 * 4. 订单状态筛选
 * 5. 订单状态修改
 */

#include "../../include/header.hpp"
using namespace std;

// 外部全局变量声明
extern GoodsList *goods_list;  // 商品列表指针

/**
 * @brief 订单控制器主函数
 * @param orders 用户的订单对象
 * @details 提供订单管理的主界面，包括以下功能：
 * 1. 退出订单管理
 * 2. 按状态查看订单项目
 * 3. 删除订单项目（仅限未支付或已确认状态）
 * 4. 修改订单项目状态
 * 5. 修改整个订单状态
 * 
 * 通过循环显示菜单并处理用户选择，直到用户选择退出
 */
void orderController(Order &orders)
{
    int choice;
    while (true)
    {
        // 获取并检查订单项目
        vector<Item> items = orders.getItems();
        if (items.empty())
        {
            cout << "\nNo items in your order.\n";
            return;
        }

        // 显示订单项目列表
        cout << "\nList of all items in your order:\n";
        for (size_t i = 0; i < items.size(); ++i)
        {
            cout << i + 1 << ". " << items[i].goods->getName()
                 << " | Quantity: " << items[i].quantity
                 << " | Status: " << items[i].status << endl;
        }

        // 显示订单管理菜单
        cout << "\nChoose an option:\n"
             << "0. Exit\n"                    // 退出订单管理
             << "1. List items by status\n"    // 按状态查看订单
             << "2. Delete an item\n"          // 删除订单项目
             << "3. Change item status\n"      // 修改项目状态
             << "4. Change order status\n"     // 修改订单状态
             << "Enter your choice: ";
        cin >> choice;

        // 根据用户选择执行相应功能
        switch (choice)
        {
        case 0:  // 退出订单管理
            cout << "Exiting order management.\n";
            return;

        case 1:  // 按状态查看订单项目
        {
            int statusChoice;
            // 显示状态选项
            cout << "\nChoose a status to filter items:\n"
                 << "1. Undefined\n"      // 未定义
                 << "2. Unpayed\n"        // 未支付
                 << "3. Not Delivered\n"  // 未发货
                 << "4. Delivered\n"      // 已发货
                 << "5. Checked\n"        // 已确认
                 << "Enter your choice: ";
            cin >> statusChoice;

            // 根据选择的状态筛选并显示订单项目
            order_status filterStatus = static_cast<order_status>(statusChoice - 1);
            cout << "\nItems with status " << statusChoice << ":\n";
            orders.iterateGoodsByStatus(filterStatus);
            break;
        }

        case 2:  // 删除订单项目
        {
            int itemIndex;
            cout << "\nEnter the item number to delete: ";
            cin >> itemIndex;

            // 验证项目编号
            if (itemIndex <= 0 || itemIndex > static_cast<int>(items.size()))
            {
                cout << "Invalid item number.\n";
                break;
            }

            // 检查项目状态并执行删除
            string itemName = items[itemIndex - 1].goods ? items[itemIndex - 1].goods->getName() : "";
            order_status st = orders.getItemStatus(itemName);
            if (st == unpayed || st == checked)  // 只允许删除未支付或已确认的项目
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

        case 3:  // 修改订单项目状态
        {
            int itemIndex, statusChoice;
            cout << "\nEnter the item number to change status: ";
            cin >> itemIndex;
            
            // 验证项目编号
            if (itemIndex <= 0 || itemIndex > static_cast<int>(items.size()))
            {
                cout << "Invalid item number.\n";
                break;
            }

            // 显示状态选项并获取新状态
            cout << "\nChoose a new status:\n"
                 << "1. Undefined\n"      // 未定义
                 << "2. Unpayed\n"        // 未支付
                 << "3. Not Delivered\n"  // 未发货
                 << "4. Delivered\n"      // 已发货
                 << "5. Checked\n"        // 已确认
                 << "Enter your choice: ";
            cin >> statusChoice;

            // 更新项目状态
            order_status newStatus = static_cast<order_status>(statusChoice - 1);
            string itemName = items[itemIndex - 1].goods ? items[itemIndex - 1].goods->getName() : "";
            if (orders.setItemStatus(itemName, newStatus))
                cout << "Item status updated successfully.\n";
            else
                cout << "Failed to update item status.\n";
            break;
        }

        case 4:  // 修改整个订单状态
            changeOrderStatus(orders);
            break;

        default:  // 无效选择
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

/**
 * @brief 修改订单状态
 * @param orders 要修改的订单对象
 * @details 处理修改订单状态的流程：
 * 1. 获取要修改的订单项目名称
 * 2. 选择新的订单状态
 * 3. 更新订单状态
 */
void changeOrderStatus(Order &orders)
{
    string itemName;
    int statusChoice;

    // 获取要修改的订单项目
    cout << "\nEnter the name of the item to change status: ";
    cin >> itemName;

    // 显示状态选项
    cout << "\nChoose a new status:\n"
         << "1. Undefined\n"      // 未定义
         << "2. Unpayed\n"        // 未支付
         << "3. Not Delivered\n"  // 未发货
         << "4. Delivered\n"      // 已发货
         << "5. Checked\n"        // 已确认
         << "Enter your choice: ";
    cin >> statusChoice;

    // 更新订单状态
    order_status newStatus = static_cast<order_status>(statusChoice - 1);

    switch (newStatus)
    {
    case undefined:      // 未定义状态
    case unpayed:        // 未支付状态
    case not_delivered:  // 未发货状态
    case delivered:      // 已发货状态
    case checked:        // 已确认状态
        if (orders.setItemStatus(itemName, newStatus))
            cout << "Order status updated successfully.\n";
        else
            cout << "Failed to update order status. Item may not exist.\n";
        break;
    default:  // 无效状态
        cout << "Invalid status choice.\n";
        break;
    }
}