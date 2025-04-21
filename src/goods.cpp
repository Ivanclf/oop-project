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

Goods *GoodsList::findGoodsByName(const string &name)
{
    auto it = goodsList.find(name);
    if (it != goodsList.end())
    {
        return &it->second;
    }
    return nullptr;
}

void GoodsList::iterateGoods() const
{
    for (const auto &pair : goodsList)
    {
        cout << "Name: " << pair.first
             << ", Category: " << pair.second.getCategory()
             << ", Price: " << pair.second.getPrice()
             << ", Storage: " << pair.second.getStorage() << endl;
    }
}

vector<string> GoodsList::findGoodsByCategory(Category category) const
{
    vector<string> result;
    for (const auto &pair : goodsList)
    {
        if (pair.second.getCategory() == category)
        {
            result.push_back(pair.first);
        }
    }
    return result;
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
        it->second = newGoods;
        return true;
    }
    return false;
}