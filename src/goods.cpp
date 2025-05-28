#include "../include/header.hpp"
using namespace std;

Goods::Goods() : name("Unnamed"), desc("No description"), category(Category::home), price(0.0), storage(0), isDiscounted(false), discountScale(0.0), discountedPrice(0.0) {}

Goods::Goods(const string &name, const string &desc, Category category, double price, int storage) : name(name), desc(desc), category(category), price(price), storage(storage), isDiscounted(false), discountScale(0), discountedPrice(price) {}

Goods::Goods(const string &name, const string &desc, Category category, double price, int storage, bool isDiscounted, double discountScale) : name(name), desc(desc), category(category), price(price), storage(storage), isDiscounted(isDiscounted), discountScale(discountScale)
{
    if (isDiscounted)
    {
        discountedPrice = price * discountScale;
    }
    else
    {
        discountedPrice = price;
    }
}

string Goods::getName() const { return name; }

void Goods::setName(const string &name) { this->name = name; }

string Goods::getDesc() const { return desc; }

void Goods::setDesc(const string &desc) { this->desc = desc; }

Category Goods::getCategory() const { return category; }

void Goods::setCategory(Category category) { this->category = category; }

void Goods::setCategory(string category) { 
    if (category == "home") {
        this->category = home;
    } else if (category == "food") {
        this->category = food;
    } else if (category == "cloth") {
        this->category = cloth;
    } else if (category == "baby_care") {
        this->category = baby_care;
    } else {
        this->category = home;
    }
}

double Goods::getPrice() const { return price; }

void Goods::setPrice(double price) { this->price = price; }

int Goods::getStorage() const { return storage; }

void Goods::setStorage(int storage) { this->storage = storage; }

bool Goods::getIsDiscounted() const { return isDiscounted; }

void Goods::setIsDiscounted(bool isDiscounted) { this->isDiscounted = isDiscounted; }

double Goods::getDiscountScale() const { return discountScale; }

void Goods::setDiscountScale(double discountScale)
{
    this->discountScale = discountScale;
    if (isDiscounted)
    {
        discountedPrice = price * discountScale;
    }
    else
    {
        discountedPrice = price;
    }
}

double Goods::getDiscountedPrice() const
{
    return discountedPrice;
}

unordered_map<string, Goods> GoodsList::getGoodsList() const
{
    return goodsList;
}

vector<Goods*> GoodsList::findGoodsByName(const string &name) const
{
    vector<Goods*> result;
    auto it = goodsList.find(name);
    if (it != goodsList.end())
        result.push_back(const_cast<Goods*>(&(it->second)));
    return result;
}

void GoodsList::iterateGoods() const
{
    for (const auto &pair : goodsList)
    {
        cout << "Name: " << pair.first
             << "\tDescripsion: " << pair.second.getDesc()
             << ",\tCategory: " << pair.second.getCategory()
             << ",\tPrice: " << pair.second.getPrice()
             << ",\tStorage: " << pair.second.getStorage();
        if (pair.second.getIsDiscounted())
            cout << ",\tDiscounted Price: " << pair.second.getDiscountedPrice();
        cout << endl;
    }
}

vector<Goods*> GoodsList::findGoodsByDesc(const string &desc) const
{
    vector<Goods*> result;
    for (auto it = goodsList.begin(); it != goodsList.end(); ++it)
    {
        if (it->second.getDesc() == desc)
        {
            result.push_back(const_cast<Goods*>(&(it->second)));
        }
    }
    return result;
}

vector<Goods*> GoodsList::findGoodsByCategory(Category category) const
{
    vector<Goods*> result;
    for (auto it = goodsList.begin(); it != goodsList.end(); ++it)
    {
        if (it->second.getCategory() == category)
        {
            result.push_back(const_cast<Goods*>(&(it->second)));
        }
    }
    return result;
}

vector<Goods*> GoodsList::findGoodsByPrice(double price) const
{
    vector<Goods*> result;
    for (auto it = goodsList.begin(); it != goodsList.end(); ++it)
    {
        if (it->second.getPrice() == price)
        {
            result.push_back(const_cast<Goods*>(&(it->second)));
        }
    }
    return result;
}

vector<Goods*> GoodsList::findGoodsByStorage(int storage) const
{
    vector<Goods*> result;
    for (auto it = goodsList.begin(); it != goodsList.end(); ++it)
    {
        if (it->second.getStorage() == storage)
        {
            result.push_back(const_cast<Goods*>(&(it->second)));
        }
    }
    return result;
}

bool GoodsList::deleteGoods(const string &name)
{
    bool result = goodsList.erase(name) > 0;
    if (result) {
        writeToFile();  // 同步到文件
    }
    return result;
}

bool GoodsList::addGoods(const string &name, const string &desc, Category category, double price, int storage)
{
    if (goodsList.find(name) != goodsList.end())
    {
        return false; // 商品已存在
    }
    goodsList[name] = Goods(name, desc, category, price, storage, false, 0.0);
    writeToFile();  // 同步到文件
    return true;
}

bool GoodsList::addGoods(const string &name, const string &desc, Category category, double price, int storage, bool isDiscounted, double discountScale)
{
    if (goodsList.find(name) != goodsList.end())
    {
        return false; // 商品已存在
    }
    goodsList[name] = Goods(name, desc, category, price, storage, isDiscounted, discountScale);
    writeToFile();  // 同步到文件
    return true;
}

bool GoodsList::addGoods(Goods goods)
{
    if (goodsList.find(goods.getName()) != goodsList.end())
    {
        return false; // 商品已存在
    }
    goodsList[goods.getName()] = goods;
    writeToFile();  // 同步到文件
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
        writeToFile();  // 同步到文件
        return true;
    }
    return false;
}

bool GoodsList::setStorage(const string &name, int decline)
{
    auto it = goodsList.find(name);
    if(it != goodsList.end())
    {
        it->second.setStorage(it->second.getStorage() - decline);
        writeToFile();  // 同步到文件
        return true;
    }
    return false;
}