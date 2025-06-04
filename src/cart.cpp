/**
 * @file cart.cpp
 * @brief 购物车模块实现
 * @details 实现了购物车类的所有方法，包括商品的添加、删除、修改数量等功能
 */

#include "../include/header.hpp"
using namespace std;

// 外部全局变量声明
extern GoodsList *goods_list;    // 商品列表指针
extern UserList *user_list;      // 用户列表指针
extern bool fileInit;            // 文件初始化状态标志

/**
 * @brief 遍历并显示购物车中的所有商品
 * @details 以列表形式显示购物车中所有商品的详细信息，包括：
 * - 商品名称
 * - 购买数量
 * - 商品价格
 * - 折扣价格（如果有折扣）
 * - 商品状态
 */
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

/**
 * @brief 根据商品名称获取购物车中的商品项
 * @param name 商品名称
 * @return Item& 返回对应商品的引用
 * @throw runtime_error 当商品不存在时抛出异常
 */
Item &Cart::getItem(string &name)
{
    for (auto &item : items)
    {
        if (item.goods && item.goods->getName() == name)
            return item;
    }
    throw std::runtime_error("Item not found in cart");
}

/**
 * @brief 获取购物车中所有商品的列表
 * @return vector<Item>& 返回商品列表的引用
 */
vector<Item> &Cart::getItems() { return items; }

/**
 * @brief 向购物车添加商品
 * @param name 商品名称
 * @param quantity 添加数量
 * @details 如果商品已存在，则增加数量；如果不存在，则创建新项
 * 添加后会自动保存到文件（如果文件系统已初始化）
 */
void Cart::addItem(string &name, int quantity)
{
    if (quantity <= 0)  // 数量必须大于0
        return;
    
    // 查找商品是否存在
    auto it = goods_list->findGoodsByName(name);
    if (it.empty())
    {
        cout << "Goods not found: " << name << endl;
        return;
    }

    Goods *goodsPtr = it.back();
    // 检查商品是否已在购物车中
    for (auto &item : items)
    {
        if (item.goods && item.goods->getName() == name)
        {
            item.quantity += quantity;  // 增加数量
            if(fileInit)
                writeToFile();  // 保存更改
            return;
        }
    }
    // 添加新商品到购物车
    items.emplace_back(goodsPtr, quantity);
    if(fileInit)
        writeToFile();  // 保存更改
}

/**
 * @brief 从购物车中删除商品
 * @param name 要删除的商品名称
 * @return bool 删除成功返回true，否则返回false
 */
bool Cart::deleteItem(string &name)
{
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        if (it->goods && it->goods->getName() == name)
        {
            items.erase(it);  // 删除商品
            if(fileInit)
                writeToFile();  // 保存更改
            return true;
        }
    }
    return false;
}

/**
 * @brief 修改购物车中商品的数量
 * @param name 商品名称
 * @param quantity 新的数量
 * @return bool 修改成功返回true，否则返回false
 * @details 如果新数量小于等于0，则删除该商品
 */
bool Cart::changeQuantity(string &name, const int quantity)
{
    for (auto &item : items)
    {
        if (item.goods && item.goods->getName() == name)
        {
            if (quantity <= 0)  // 数量无效时删除商品
            {
                bool result = deleteItem(name);
                if (result && fileInit) {
                    writeToFile();  // 保存更改
                }
                return result;
            }
            item.quantity = quantity;  // 更新数量
            if(fileInit)
                writeToFile();  // 保存更改
            return true;
        }
    }
    return false;
}

/**
 * @brief 获取购物车中的商品数量
 * @return int 返回购物车中的商品种类数量
 */
int Cart::getSize() const { return items.size(); }
