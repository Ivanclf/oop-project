/**
 * @file cartController.cpp
 * @brief 购物车控制器模块
 * @details 实现了购物车管理的主要功能，包括：
 * 1. 购物车商品管理（添加、删除、修改数量）
 * 2. 购物车商品查看
 * 3. 购物车商品转订单
 * 4. 商品库存管理
 */

#include "../../include/header.hpp"
using namespace std;

// 外部全局变量声明
extern GoodsList *goods_list;  // 商品列表指针
extern bool fileInit;          // 文件初始化标志

/**
 * @brief 购物车控制器主函数
 * @param userCart 用户的购物车对象
 * @param order 用户的订单对象
 * @details 提供购物车管理的主界面，包括以下功能：
 * 1. 退出购物车
 * 2. 删除购物车商品
 * 3. 修改商品数量
 * 4. 将购物车所有商品加入订单
 * 5. 将单个商品加入订单
 * 
 * 通过循环显示菜单并处理用户选择，直到用户选择退出
 */
void cartController(Cart &userCart, Order &order)
{
    int choice, quantity = 0;
    bool temp = false;
    string name;
    while (true)
    {
        // 显示购物车内容
        cout << "\nThis is your cart. What you have chosen is on the list:\n";
        userCart.iterateGoods();
        
        // 显示购物车功能菜单
        cout << "\n\n0. Exit"                    // 退出购物车
             << "\n1. Delete a item"            // 删除商品
             << "\n2. Change the quantity of an item"  // 修改商品数量
             << "\n3. Add all items in cart to order"  // 全部加入订单
             << "\n4. Add a single item in cart to order"  // 单个加入订单
             << "\nChoose an option that you wanna do:\t";
        cin >> choice;

        // 根据用户选择执行相应功能
        switch (choice)
        {
        case 0:  // 退出购物车
            cout << "ByeBye!~\n";
            return;
        case 1:  // 删除商品
            cout << "Input the name of the item you want to delete: ";
            cin >> name;
            if (userCart.deleteItem(name))
                cout << "you have delete a item successfully\n";
            else
                cout << "delete failed! check if you have inputted right name\n";
            break;
        case 2:  // 修改商品数量
            cout << "Input the name of the item you want to change: ";
            cin >> name;
            cout << "Input the new quantity:\t";
            cin >> quantity;
            if (!quantity)  // 数量为0时删除商品
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
            if(fileInit)
                writeToFile();  // 保存更改到文件
            break;
        case 3:  // 将购物车所有商品加入订单
            if (userCart.getSize() == 0)
            {
                cout << "Cart is empty, nothing to add.\n";
                break;
            }
            // 设置所有商品状态为未支付
            for (auto &it : userCart.getItems())
                it.status = unpayed;
            
            // 将所有商品添加到订单
            for (auto &it : userCart.getItems())
            {
                if (it.goods)
                {
                    string gname = it.goods->getName();
                    order.addItem(gname, it.quantity, it.status);
                }
            }
            cout << "All items in cart have been added to your order.\n";
            userCart.getItems().clear();  // 清空购物车
            if(fileInit)
                writeToFile();  // 保存更改到文件
            break;
        case 4:  // 将单个商品加入订单
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
            if(fileInit)
                writeToFile();  // 保存更改到文件
        end_case4:
            break;
        default:  // 无效选择
            cout << "you have pressed a wrong number, please press again!\n";
            break;
        }
    }
}

/**
 * @brief 添加新商品到购物车
 * @param userCart 用户的购物车对象
 * @details 处理添加商品到购物车的流程：
 * 1. 获取用户输入的商品名称和数量
 * 2. 验证商品是否存在
 * 3. 验证数量是否有效
 * 4. 将商品添加到购物车
 */
void addNew(Cart &userCart)
{
    string name;
    int quantity;
    vector<Goods*> temp;
    while (true)
    {
        // 获取用户输入
        cout << "\nwhich one would you like to choose?"
             << "\n(input name and quantity of goods)"
             << "\nname: ";
        cin >> name;
        cout << "quantity: ";
        cin >> quantity;

        // 查找商品并验证
        temp = goods_list->findGoodsByName(name);
        if (temp.empty() || quantity <= 0)
        {
            cout << "You have input wrong parameter(s)!";
            break;
        }
        else
        {
            // 添加商品到购物车
            userCart.addItem(name, quantity);
            cout << "\noperation succeed!";
            break;
        }
    }
}