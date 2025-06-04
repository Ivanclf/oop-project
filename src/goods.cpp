/**
 * @file goods.cpp
 * @brief 商品模块实现
 * @details 实现了商品类和商品列表类的所有方法，包括商品的增删改查、库存管理等功能
 */

#include "../include/header.hpp"
using namespace std;
extern bool fileInit;  // 文件初始化状态标志

/**
 * @brief 商品类默认构造函数
 * @details 初始化一个未命名的商品，所有属性设置为默认值
 */
Goods::Goods() : name("Unnamed"), desc("No description"), category(Category::home), price(0.0), storage(0), isDiscounted(false), discountScale(0.0), discountedPrice(0.0) {}

/**
 * @brief 商品类构造函数（无折扣）
 * @param name 商品名称
 * @param desc 商品描述
 * @param category 商品类别
 * @param price 商品价格
 * @param storage 库存数量
 */
Goods::Goods(const string &name, const string &desc, Category category, double price, int storage) : name(name), desc(desc), category(category), price(price), storage(storage), isDiscounted(false), discountScale(0), discountedPrice(price) {}

/**
 * @brief 商品类构造函数（带折扣）
 * @param name 商品名称
 * @param desc 商品描述
 * @param category 商品类别
 * @param price 商品价格
 * @param storage 库存数量
 * @param isDiscounted 是否打折
 * @param discountScale 折扣比例
 */
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

// 商品属性的getter和setter方法
string Goods::getName() const { return name; }
void Goods::setName(const string &name) { this->name = name; }

string Goods::getDesc() const { return desc; }
void Goods::setDesc(const string &desc) { this->desc = desc; }

Category Goods::getCategory() const { return category; }
void Goods::setCategory(Category category) { this->category = category; }

/**
 * @brief 通过字符串设置商品类别
 * @param category 类别字符串（"0":家居, "1":食品, "2":服装, "3":母婴）
 */
void Goods::setCategory(string category) { 
    if (category == "0") {
        this->category = home;
    } else if (category == "1") {
        this->category = food;
    } else if (category == "2") {
        this->category = cloth;
    } else if (category == "3") {
        this->category = baby_care;
    } else {
        this->category = home;  // 默认类别
    }
}

double Goods::getPrice() const { return price; }
void Goods::setPrice(double price) { this->price = price; }

int Goods::getStorage() const { return storage; }
void Goods::setStorage(int storage) { this->storage = storage; }

bool Goods::getIsDiscounted() const { return isDiscounted; }
void Goods::setIsDiscounted(bool isDiscounted) { this->isDiscounted = isDiscounted; }

double Goods::getDiscountScale() const { return discountScale; }

/**
 * @brief 设置折扣比例
 * @param discountScale 新的折扣比例
 * @details 同时更新折扣价格
 */
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

/**
 * @brief 获取商品列表
 * @return unordered_map<string, Goods> 返回所有商品的映射表
 */
unordered_map<string, Goods> GoodsList::getGoodsList() const
{
    return goodsList;
}

/**
 * @brief 根据名称查找商品
 * @param name 商品名称
 * @return vector<Goods*> 返回匹配商品的指针列表
 */
vector<Goods*> GoodsList::findGoodsByName(const string &name) const
{
    vector<Goods*> result;
    auto it = goodsList.find(name);
    if (it != goodsList.end())
        result.push_back(const_cast<Goods*>(&(it->second)));
    return result;
}

/**
 * @brief 遍历并显示所有商品信息
 * @details 显示每个商品的名称、描述、类别、价格、库存等信息
 */
void GoodsList::iterateGoods() const
{
    if(goodsList.empty()) {
        cout << "No goods" << endl;
        return;
    }
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

/**
 * @brief 根据描述查找商品
 * @param desc 商品描述
 * @return vector<Goods*> 返回匹配商品的指针列表
 */
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

/**
 * @brief 根据类别查找商品
 * @param category 商品类别
 * @return vector<Goods*> 返回匹配商品的指针列表
 */
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

/**
 * @brief 根据价格查找商品
 * @param price 商品价格
 * @return vector<Goods*> 返回匹配商品的指针列表
 */
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

/**
 * @brief 根据库存查找商品
 * @param storage 库存数量
 * @return vector<Goods*> 返回匹配商品的指针列表
 */
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

/**
 * @brief 删除商品
 * @param name 要删除的商品名称
 * @return bool 删除成功返回true，否则返回false
 */
bool GoodsList::deleteGoods(const string &name)
{
    bool result = goodsList.erase(name) > 0;
    if (result && fileInit) {
        writeToFile();  // 同步到文件
    }
    return result;
}

/**
 * @brief 添加商品（无折扣）
 * @param name 商品名称
 * @param desc 商品描述
 * @param category 商品类别
 * @param price 商品价格
 * @param storage 库存数量
 * @return bool 添加成功返回true，否则返回false
 */
bool GoodsList::addGoods(const string &name, const string &desc, Category category, double price, int storage)
{
    if (goodsList.find(name) != goodsList.end())
    {
        return false; // 商品已存在
    }
    goodsList[name] = Goods(name, desc, category, price, storage, false, 0.0);
    if(fileInit)
        writeToFile();  // 同步到文件
    return true;
}

/**
 * @brief 添加商品（带折扣）
 * @param name 商品名称
 * @param desc 商品描述
 * @param category 商品类别
 * @param price 商品价格
 * @param storage 库存数量
 * @param isDiscounted 是否打折
 * @param discountScale 折扣比例
 * @return bool 添加成功返回true，否则返回false
 */
bool GoodsList::addGoods(const string &name, const string &desc, Category category, double price, int storage, bool isDiscounted, double discountScale)
{
    if (goodsList.find(name) != goodsList.end())
    {
        return false; // 商品已存在
    }
    goodsList[name] = Goods(name, desc, category, price, storage, isDiscounted, discountScale);
    if(fileInit)
        writeToFile();  // 同步到文件
    return true;
}

/**
 * @brief 添加商品对象
 * @param goods 要添加的商品对象
 * @return bool 添加成功返回true，否则返回false
 */
bool GoodsList::addGoods(Goods goods)
{
    if (goodsList.find(goods.getName()) != goodsList.end())
    {
        return false; // 商品已存在
    }
    goodsList[goods.getName()] = goods;
    if(fileInit)
        writeToFile();  // 同步到文件
    return true;
}

/**
 * @brief 更新商品信息
 * @param name 要更新的商品名称
 * @param newGoods 新的商品信息
 * @return bool 更新成功返回true，否则返回false
 */
bool GoodsList::updateGoods(const string &name, const Goods &newGoods)
{
    auto it = goodsList.find(name);
    if (it != goodsList.end())
    {
        Goods updateGoods = newGoods;
        goodsList.erase(it);
        goodsList[updateGoods.getName()] = updateGoods;
        if(fileInit)
            writeToFile();  // 同步到文件
        return true;
    }
    return false;
}

/**
 * @brief 更新商品库存
 * @param name 商品名称
 * @param decline 减少的库存数量
 * @return bool 更新成功返回true，否则返回false
 */
bool GoodsList::setStorage(const string &name, int decline)
{
    auto it = goodsList.find(name);
    if(it != goodsList.end())
    {
        it->second.setStorage(it->second.getStorage() - decline);
        if(fileInit)
            writeToFile();  // 同步到文件
        return true;
    }
    return false;
}