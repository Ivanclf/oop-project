#include "../include/header.hpp"
using namespace std;

Goods::Goods() : name("Unnamed"), desc("No description"), category(Category::home), price(0.0), storage(0) {}

Goods::Goods(const string &name, const string &desc, Category category, double price, int storage)
    : name(name), desc(desc), category(category), price(price), storage(storage) {}

string Goods::getName() const { return name; }

void Goods::setName(const string &name) { this->name = name; }

string Goods::getDesc() const { return desc; }

void Goods::setDesc(const string &desc) { this->desc = desc; }

Category Goods::getCategory() const { return category; }

void Goods::setCategory(Category category) { this->category = category; }

double Goods::getPrice() const { return price; }

void Goods::setPrice(double price) { this->price = price; }

int Goods::getStorage() const { return storage; }

void Goods::setStorage(int storage) { this->storage = storage; }

#include "../include/header.hpp"
using namespace std;

unordered_map<string, Goods> GoodsList::getGoodsList() const
{
    return goodsList;
}

vector<Goods> GoodsList::findGoodsByName(const string &name) const
{
    vector<Goods> result;
    auto it = goodsList.find(name);
    if (it != goodsList.end())
        result.push_back(it->second);
    return result;
}

void GoodsList::iterateGoods() const
{
    for (const auto &pair : goodsList)
    {
        cout << "Name: " << pair.first
             << "Descripsion: " << pair.second.getDesc()
             << ", Category: " << pair.second.getCategory()
             << ", Price: " << pair.second.getPrice()
             << ", Storage: " << pair.second.getStorage() << "\n";
    }
}

template <typename T>
vector<Goods> GoodsList::findGoods(T value, int param) const
{
    vector<Goods> result;
    switch (param)
    {
    case 1: // desc
        for (auto it = goodsList.begin(); it != goodsList.end(); ++it)
            if (*it->second.getDesc() == value)
                result.push_back(*it);
        break;
    case 2: // category
        for (auto it = goodsList.begin(); it != goodsList.end(); ++it)
            if (*it->second.getCategory() == value)
                result.push_back(*it);
    case 3: // price
        for (auto it = goodsList.begin(); it != goodsList.end(); ++it)
            if (*it->second.getPrice() == value)
                result.push_back(*it);
    case 4: // storage
        for (auto it = goodsList.begin(); it != goodsList.end(); ++it)
            if (*ir->second.getStorage() == value)
                result.push_back(*it);
    default:
        break;
    }
}

bool GoodsList::deleteGoods(const string &name)
{
    return goodsList.erase(name) > 0;
}

bool GoodsList::addGoods(const string &name, const string &desc, Category category, double price, int storage)
{
    if (goodsList.find(name) != goodsList.end())
    {
        return false; // 商品已存在
    }
    goodsList[name] = Goods(name, desc, category, price, storage);
    return true;
}

bool GoodsList::addGoods(Goods goods)
{
    if (goodsList.find(goods.getName()) != goodsList.end())
    {
        return false; // 商品已存在
    }
    goodsList[goods.getName()] = goods;
    return true;
}

bool GoodsList::updateGoods(const string &name, const Goods &newGoods)
{
    auto it = goodsList.find(name);
    if (it != goodsList.end())
    {
        Goods updateGoods = newGoods;
        goodsList.erase(it);
        goodsList[updateGoods.getName()] = updateGoods;
        return true;
    }
    return false;
}