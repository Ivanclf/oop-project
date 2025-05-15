#include "../include/header.hpp"
using namespace std;

extern GoodsList *goods_list;

Order::Order() {}
Order::Order(const vector<Item> &items) : orderList(items) {}

vector<Item> Order::getItems() const
{
    return orderList;
}

void Order::sortByName()
{
    sort(orderList.begin(), orderList.end(), [](const Item &a, const Item &b) {
        return a.item.getName() < b.item.getName();
    });
}

void Order::sortByStatus(vector<Order> &orders)
{
    sort(orders.begin(), orders.end(), [](const Order &a, const Order &b) {
        return a.getItems().size() < b.getItems().size(); 
    });
}

void Order::printAllItems() const
{
    for (const auto &item : orderList)
    {
        cout << "Name: " << item.item.getName()
             << ", Quantity: " << item.quantity
             << ", Status: " << item.status << endl;
    }
}

void Order::printItemsByStatus(order_status filterStatus) const
{
    for (const auto &item : orderList)
    {
        if (item.status == filterStatus)
        {
            cout << "Name: " << item.item.getName()
                 << ", Quantity: " << item.quantity
                 << ", Status: " << item.status << endl;
        }
    }
}

void Order::addItem(const Item &item)
{
    for (auto &it : orderList)
    {
        if (it.item.getName() == item.item.getName())
        {
            int maxQuantity = it.item.getStorage(); 
            if (it.quantity + item.quantity > maxQuantity)
            {
                it.quantity = maxQuantity; 
                cout << "Quantity for item \"" << it.item.getName() << "\" adjusted to maximum storage: " << maxQuantity << endl;
            }
            else
            {
                it.quantity += item.quantity; 
            }

            
            if (it.status == unpayed)
            {
                cout << "Item \"" << it.item.getName() << "\" is unpayed. Triggering autoChangeStatus...\n";
                autoChangeStatus();
            }
            return;
        }
    }

    
    if (item.quantity > item.item.getStorage())
    {
        Item newItem = item;
        newItem.quantity = item.item.getStorage(); 
        cout << "Quantity for new item \"" << newItem.item.getName() << "\" adjusted to maximum storage: " << newItem.quantity << endl;
        orderList.push_back(newItem);
    }
    else
    {
        orderList.push_back(item);
    }

    
    if (item.status == unpayed)
    {
        cout << "Item \"" << item.item.getName() << "\" is unpayed. Triggering autoChangeStatus...\n";
        autoChangeStatus();
    }
}

void Order::addItem(const vector<Item> &itemList)
{
    for (const auto &newItem : itemList)
    {
        bool found = false;
        for (auto &existingItem : orderList)
        {
            if (existingItem.item.getName() == newItem.item.getName())
            {
                int maxQuantity = existingItem.item.getStorage(); 
                if (existingItem.quantity + newItem.quantity > maxQuantity)
                {
                    existingItem.quantity = maxQuantity; 
                    cout << "Quantity for item \"" << existingItem.item.getName() << "\" adjusted to maximum storage: " << maxQuantity << endl;
                }
                else
                {
                    existingItem.quantity += newItem.quantity; 
                }

                
                if (existingItem.status == unpayed)
                {
                    cout << "Item \"" << existingItem.item.getName() << "\" is unpayed. Triggering autoChangeStatus...\n";
                    autoChangeStatus();
                }
                found = true;
                break;
            }
        }
        if (!found)
        {
            
            if (newItem.quantity > newItem.item.getStorage())
            {
                Item adjustedItem = newItem;
                adjustedItem.quantity = newItem.item.getStorage(); 
                cout << "Quantity for new item \"" << adjustedItem.item.getName() << "\" adjusted to maximum storage: " << adjustedItem.quantity << endl;
                orderList.push_back(adjustedItem);
            }
            else
            {
                orderList.push_back(newItem);
            }

            
            if (newItem.status == unpayed)
            {
                cout << "Item \"" << newItem.item.getName() << "\" is unpayed. Triggering autoChangeStatus...\n";
                autoChangeStatus();
            }
        }
    }
}

bool Order::deleteItem(const string &itemName)
{
    for (auto it = orderList.begin(); it != orderList.end(); ++it)
    {
        if (it->item.getName() == itemName)
        {
            orderList.erase(it);
            return true;
        }
    }
    return false;
}

bool Order::setItemStatus(const string &itemName, order_status newStatus)
{
    for (auto &it : orderList)
    {
        if (it.item.getName() == itemName)
        {
            it.status = newStatus;
            return true;
        }
    }
    return false;
}

order_status Order::getItemStatus(const string &itemName) const
{
    for (const auto &it : orderList)
    {
        if (it.item.getName() == itemName)
        {
            return it.status;
        }
    }
    return undefined; 
}

void Order::autoChangeStatus()
{
    for (auto &item : orderList)
    {
        if (item.status == unpayed)
        {
            cout << "Order item \"" << item.item.getName() << "\" is currently unpayed. Changing status...\n";

            std::this_thread::sleep_for(std::chrono::seconds(5));
            item.status = not_deliverd;
            cout << "Order item \"" << item.item.getName() << "\" status changed to not_deliverd.\n";

            std::this_thread::sleep_for(std::chrono::seconds(5));
            item.status = deliverd;
            cout << "Order item \"" << item.item.getName() << "\" status changed to deliverd.\n";
        }
    }
}

void Order::changeStorage()
{
    for (auto &item : orderList)
    {
        if (item.status == not_deliverd) 
        {
            auto it = goods_list->getGoodsList().find(item.item.getName());
            if (it != goods_list->getGoodsList().end()) 
            {
                Goods &goods = it->second;
                int currentStorage = goods.getStorage();
                if (currentStorage >= item.quantity)
                {
                    goods.setStorage(currentStorage - item.quantity); 
                    cout << "Storage updated for item \"" << goods.getName() << "\". New storage: " << goods.getStorage() << endl;
                }
                else
                    cout << "Insufficient storage for item \"" << goods.getName() << "\". Cannot fulfill the order.\n";
            }
            else
                cout << "Item \"" << item.item.getName() << "\" not found in goods list.\n";
        }
    }
}