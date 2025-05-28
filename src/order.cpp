#include "../include/header.hpp"
using namespace std;

extern GoodsList *goods_list;
extern UserList *user_list;

vector<Item> &Order::getItems() { return orderList; }

void Order::sortByName() {
    sort(orderList.begin(), orderList.end(), [](const Item &a, const Item &b) {
        return a.goods->getName() < b.goods->getName();
    });
}

void Order::sortByStatus() {
    sort(orderList.begin(), orderList.end(), [](const Item &a, const Item &b) {
        return a.status < b.status;
    });
}

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

void Order::iterateGoodsByStatus(order_status filterStatus) const {
    vector<Item> filteredItems;
    for (const auto &item : orderList) {
        if (item.status == filterStatus && item.goods) {
            filteredItems.push_back(item);
        }
    }
    if (filteredItems.empty()) {
        cout << "No items with status " << printStatus(filterStatus) << ".\n";
        return;
    }
    cout << "\nItems with status " << printStatus(filterStatus) << ":\n";
    for (const auto &item : filteredItems) {
        cout << "Name: " << item.goods->getName()
             << ", Quantity: " << item.quantity
             << ", Status: " << printStatus(item.status) << '\n';
    }
}

void Order::addItem(string &name, int quantity, order_status status) {
    if (quantity <= 0)
        return;
    auto it = goods_list->findGoodsByName(name);
    if (it.empty()) {
        cout << "Goods not found: " << name << endl;
        return;
    }

    Goods* goodsPtr = it.back();
    for (auto &item : orderList) {
        if (item.goods && item.goods->getName() == name) {
            if(item.quantity + quantity > goodsPtr->getStorage()) {
                cout << "Not enough storage for " << name  << "\ntake the maximum" << endl;
                item.quantity = goodsPtr->getStorage();
                goodsPtr->setStorage(0);
                autoChangeStatus();
                writeToFile();
                return;
            }
            item.quantity += quantity;
            item.status = status;
            goodsPtr->setStorage(goodsPtr->getStorage() - quantity);
            autoChangeStatus();
            writeToFile();
            return;
        }
    }
    orderList.emplace_back(goodsPtr, quantity, status);
    writeToFile();
}

bool Order::deleteItem(string &name) {
    for (auto it = orderList.begin(); it != orderList.end(); ++it) {
        if (it->goods && it->goods->getName() == name) {
            orderList.erase(it);
            writeToFile();
            return true;
        }
    }
    return false;
}

bool Order::setItemStatus(const string &itemName, order_status newStatus) {
    for (auto &item : orderList) {
        if (item.goods && item.goods->getName() == itemName) {
            item.status = newStatus;
            writeToFile();
            return true;
        }
    }
    return false;
}

order_status &Order::getItemStatus(string &itemName) {
    for (auto &item : orderList) {
        if (item.goods && item.goods->getName() == itemName) {
            return item.status;
        }
    }
    static order_status invalid_status = undefined;
    return invalid_status;
}

void Order::autoChangeStatus() {
    for (auto &item : orderList) {
        if (item.status == unpayed) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            item.status = not_delivered;
            writeToFile();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            item.status = delivered;
            writeToFile();
        }
    }
}

void Order::changeStorage() {
    for (auto &item : orderList) {
        if (item.status == not_delivered && item.goods) {
            int currentStorage = item.goods->getStorage();
            if (currentStorage >= item.quantity) {
                item.goods->setStorage(currentStorage - item.quantity);
                writeToFile();
            }
        }
    }
}

string &Order::printStatus(order_status status) const {
    static string statusStr;
    switch (status) {
        case undefined:
            statusStr = "Undefined";
            break;
        case unpayed:
            statusStr = "Unpayed";
            break;
        case not_delivered:
            statusStr = "Not Delivered";
            break;
        case delivered:
            statusStr = "Delivered";
            break;
        case checked:
            statusStr = "Checked";
            break;
        default:
            statusStr = "Unknown Status";
    }
    return statusStr;
}