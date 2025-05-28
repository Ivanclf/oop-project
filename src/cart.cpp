#include "../include/header.hpp"
using namespace std;

extern GoodsList *goods_list;
extern UserList *user_list;
extern bool fileInit;

void Cart::iterateGoods() const
{
    if (items.empty())
    {
        cout << "No items in the cart.\n";
        return;
    }
    cout << "\nList of all items in your cart:\n";
    for (const auto &item : items)
    {
        if (item.goods)
        {
            cout << "Name: " << item.goods->getName()
                 << ", Quantity: " << item.quantity
                 << ", Price: " << item.goods->getPrice();
            if (item.goods->getIsDiscounted())
                cout << ", Discounted Price: " << item.goods->getDiscountedPrice();
            cout << ", Status: " << item.status << '\n';
        }    
    }
}

Item &Cart::getItem(string &name)
{
    for (auto &item : items)
    {
        if (item.goods && item.goods->getName() == name)
            return item;
    }
    throw std::runtime_error("Item not found in cart");
}

vector<Item> &Cart::getItems() { return items; }

void Cart::addItem(string &name, int quantity)
{
    if (quantity <= 0)
        return;
    auto it = goods_list->findGoodsByName(name);
    if (it.empty())
    {
        cout << "Goods not found: " << name << endl;
        return;
    }

    Goods *goodsPtr = it.back();
    for (auto &item : items)
    {
        if (item.goods && item.goods->getName() == name)
        {
            item.quantity += quantity;
            if(fileInit)
                writeToFile();
            return;
        }
    }
    items.emplace_back(goodsPtr, quantity);
    if(fileInit)
        writeToFile();
}

bool Cart::deleteItem(string &name)
{
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        if (it->goods && it->goods->getName() == name)
        {
            items.erase(it);
            if(fileInit)
                writeToFile();
            return true;
        }
    }
    return false;
}

bool Cart::changeQuantity(string &name, const int quantity)
{
    for (auto &item : items)
    {
        if (item.goods && item.goods->getName() == name)
        {
            if (quantity <= 0)
            {
                bool result = deleteItem(name);
                if (result && fileInit) {
                    writeToFile();
                }
                return result;
            }
            item.quantity = quantity;
            if(fileInit)
                writeToFile();
            return true;
        }
    }
    return false;
}

int Cart::getSize() const { return items.size(); }
