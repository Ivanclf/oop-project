#include "../include/header.hpp"
using namespace std;
extern GoodsList *goods_list;

void Cart::iterateGoods() const
{
    int count = 1;
    double total = 0;
    if (items.empty())
    {
        cout << "\nOops! the cart is empty, go and find something fine!";
        return;
    }
    for (const auto &it : items)
    {
        cout << count++ << ": Name: " << it.item.getName()
             << "\tDescripsion: " << it.item.getDesc()
             << "\tPrice: " << it.item.getPrice()
             << "\tquantity: " << it.quantity << "\n";
        total += it.item.getPrice() * it.quantity;
    }
    cout << "total price: " << total;

    getchar();
    cout << "\nPress any key to continue";
    getchar();
}

Item &Cart::getItem(const int order) { return items[order - 1]; }

void Cart::addItem(Goods *goods)
{
    for (auto &it : this->items)
    {
        if (it.item.getName() == goods->getName())
        {
            it.quantity++;
            return;
        }
    }
    this->items.push_back(Item(*goods, 1));
}

void Cart::addItem(Item &item)
{
    for (auto &it : items)
    {
        if (it.item.getName() == item.item.getName())
        {
            it.quantity++;
            return;
        }
    }
    items.push_back(item);
}

bool Cart::deleteItem(const int order)
{
    if (order <= 0 || (long unsigned int)order > items.size())
        return false;
    items.erase(items.begin() + (order - 1));
    return true;
}

bool Cart::changeQuantity(Item &item, const int quantity)
{
    if (item.item.getStorage() < quantity)
        return false;
    else
    {
        item.quantity = quantity;
        goods_list->setStorage(item.item.getName(), quantity);
    }
    return true;
}

int Cart::getSize() const { return items.size(); }