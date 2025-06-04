/**
 * @file order.cpp
 * @brief 订单模块实现
 * @details 实现了订单类的所有方法，包括订单的创建、修改、状态管理等功能
 */

#include "../include/header.hpp"
using namespace std;

// 外部全局变量声明
extern GoodsList *goods_list;    // 商品列表指针
extern UserList *user_list;      // 用户列表指针
extern bool fileInit;            // 文件初始化状态标志

/**
 * @brief 获取订单中的所有商品项
 * @return vector<Item>& 返回订单商品列表的引用
 */
vector<Item> &Order::getItems() { return orderList; }

/**
 * @brief 按商品名称对订单进行排序
 * @details 使用商品名称的字典序进行排序
 */
void Order::sortByName() {
    sort(orderList.begin(), orderList.end(), [](const Item &a, const Item &b) {
        return a.goods->getName() < b.goods->getName();
    });
}

/**
 * @brief 按订单状态对订单进行排序
 * @details 使用订单状态的枚举值进行排序
 */
void Order::sortByStatus() {
    sort(orderList.begin(), orderList.end(), [](const Item &a, const Item &b) {
        return a.status < b.status;
    });
}

/**
 * @brief 遍历并显示订单中的所有商品
 * @details 显示每个商品的名称、数量和状态
 */
void Order::iterateGoods() const {
    if(orderList.empty()) {
        cout << "No items in the order.\n";
        return;
    }
    cout << "\nList of all items in your order:\n";
    for (const auto &item : orderList) {
        if (item.goods) {
            cout << "Name: " << item.goods->getName()
                 << ", Quantity: " << item.quantity
                 << ", Status: " << printStatus(item.status) << '\n';
        }
    }
}

/**
 * @brief 按状态筛选并显示订单商品
 * @param filterStatus 要筛选的订单状态
 * @details 只显示指定状态的订单商品
 */
void Order::iterateGoodsByStatus(order_status filterStatus) const {
    vector<Item> filteredItems;
    // 筛选指定状态的商品
    for (const auto &item : orderList) {
        if (item.status == filterStatus && item.goods) {
            filteredItems.push_back(item);
        }
    }
    if (filteredItems.empty()) {
        cout << "No items with status " << printStatus(filterStatus) << ".\n";
        return;
    }
    // 显示筛选结果
    cout << "\nItems with status " << printStatus(filterStatus) << ":\n";
    for (const auto &item : filteredItems) {
        cout << "Name: " << item.goods->getName()
             << ", Quantity: " << item.quantity
             << ", Status: " << printStatus(item.status) << '\n';
    }
}

/**
 * @brief 向订单添加商品
 * @param name 商品名称
 * @param quantity 添加数量
 * @param status 订单状态
 * @details 添加商品时会检查库存，如果库存不足会调整购买数量
 */
void Order::addItem(string &name, int quantity, order_status status) {
    if (quantity <= 0)  // 数量必须大于0
        return;
    
    // 查找商品是否存在
    auto it = goods_list->findGoodsByName(name);
    if (it.empty()) {
        cout << "Goods not found: " << name << endl;
        return;
    }

    Goods* goodsPtr = it.back();
    // 检查商品是否已在订单中
    for (auto &item : orderList) {
        if (item.goods && item.goods->getName() == name) {
            // 检查库存是否充足
            if(item.quantity + quantity > goodsPtr->getStorage()) {
                cout << "Not enough storage for " << name  << "\ntake the maximum" << endl;
                item.quantity = goodsPtr->getStorage();  // 调整购买数量为最大库存
                goodsPtr->setStorage(0);  // 清空库存
                if(fileInit)
                    writeToFile();
                return;
            }
            item.quantity += quantity;  // 增加数量
            item.status = status;       // 更新状态
            goodsPtr->setStorage(goodsPtr->getStorage() - quantity);  // 更新库存
            if(fileInit)
                writeToFile();
            return;
        }
    }
    // 添加新商品到订单
    orderList.emplace_back(goodsPtr, quantity, status);
    if(fileInit)
        writeToFile();
}

/**
 * @brief 从订单中删除商品
 * @param name 要删除的商品名称
 * @return bool 删除成功返回true，否则返回false
 */
bool Order::deleteItem(string &name) {
    for (auto it = orderList.begin(); it != orderList.end(); ++it) {
        if (it->goods && it->goods->getName() == name) {
            orderList.erase(it);  // 删除商品
            if(fileInit)
                writeToFile();
            return true;
        }
    }
    return false;
}

/**
 * @brief 设置订单商品的状态
 * @param itemName 商品名称
 * @param newStatus 新状态
 * @return bool 设置成功返回true，否则返回false
 */
bool Order::setItemStatus(const string &itemName, order_status newStatus) {
    for (auto &item : orderList) {
        if (item.goods && item.goods->getName() == itemName) {
            item.status = newStatus;  // 更新状态
            if(fileInit)
                writeToFile();
            return true;
        }
    }
    return false;
}

/**
 * @brief 获取订单商品的状态
 * @param itemName 商品名称
 * @return order_status& 返回商品状态的引用，如果商品不存在则返回undefined状态
 */
order_status &Order::getItemStatus(string &itemName) {
    for (auto &item : orderList) {
        if (item.goods && item.goods->getName() == itemName) {
            return item.status;
        }
    }
    static order_status invalid_status = undefined;  // 无效状态
    return invalid_status;
}

/**
 * @brief 更新订单商品的库存
 * @details 对于未发货的商品，检查并更新库存
 */
void Order::changeStorage() {
    for (auto &item : orderList) {
        if (item.status == not_delivered && item.goods) {
            int currentStorage = item.goods->getStorage();
            if (currentStorage >= item.quantity) {
                item.goods->setStorage(currentStorage - item.quantity);  // 减少库存
                if(fileInit)
                    writeToFile();
            }
        }
    }
}

/**
 * @brief 将订单状态转换为可读字符串
 * @param status 订单状态
 * @return string& 返回状态对应的字符串描述
 */
string &Order::printStatus(order_status status) const {
    static string statusStr;
    switch (status) {
        case undefined:
            statusStr = "Undefined";      // 未定义
            break;
        case unpayed:
            statusStr = "Unpayed";        // 未支付
            break;
        case not_delivered:
            statusStr = "Not Delivered";  // 未发货
            break;
        case delivered:
            statusStr = "Delivered";      // 已发货
            break;
        case checked:
            statusStr = "Checked";        // 已确认
            break;
        default:
            statusStr = "Unknown Status"; // 未知状态
    }
    return statusStr;
}