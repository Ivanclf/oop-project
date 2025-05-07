#include "../include/header.hpp"
using namespace std;
extern GoodsList *goods_list;

void cart::iterateGoods() const
{
    int count = 1;
    for (const auto &it : cart)
    {
        cout << ++count << ": Name: " << it.item.getName()
             << "\tDescripsion: " << it.item.getDesc()
             << "\tPrice" << it.item.getPrice() << "\n";
        getchar();
        cout << "Press any key to continue\n";
        getchar();
    }
}

Item cart::getItem(const int order)
{
    if (order <= 0 || order > cart.size())
        return {};
    return cart[order - 1];
}

void cart::addItem(Goods *item)
{
    for (auto &it : cart)
    {
        if (it.item.getName() == item->getName())
        {
            it.quantity++;
            return;
        }
    }
    cart.push_back(Item(*item, 1));
}

bool cart::deleteItem(const int order)
{
    if (order <= 0 || order > cart.size())
        return false;
    cart.erase(cart.begin() + (order - 1));
    return true;
}

bool cart::changeQuantity(Item item, const int quantity)
{
    if(item.item.getStorage() < quantity)
        return false;
    else 
    {
        item.quantity = quantity;
        goods_list->setStorage(item.item.getName(), quantity);
    }
    return true;
        
}

int cart::getSize() const { return cart.size(); }