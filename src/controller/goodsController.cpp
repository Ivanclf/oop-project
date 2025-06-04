/**
 * @file goodsController.cpp
 * @brief 商品控制器模块
 * @details 实现了商品管理的主要功能，包括：
 * 1. 商品浏览和搜索
 * 2. 商品添加和更新
 * 3. 商品删除
 * 4. 商品分类管理
 * 5. 商品库存管理
 */

#include "../../include/header.hpp"
using namespace std;

// 外部全局变量声明
extern UserList *user_list;    // 用户列表指针
extern GoodsList *goods_list;  // 商品列表指针

/**
 * @brief 显示所有商品列表
 * @param user 当前用户对象
 * @details 显示系统中所有商品的信息，并根据用户角色提供不同的功能：
 * 1. 管理员：仅显示商品列表
 * 2. 顾客：显示商品列表并提供添加到购物车的选项
 */
void listAllGoods(User &user)
{
    char option;
    auto cart = &(user.getCart());
    goods_list->iterateGoods();  // 显示所有商品
    if(user.getRole() == customer)  // 顾客用户可以选择添加商品
    {
        cout << "\nNeed to add something?\n(1 for yes, else for no): ";
        cin >> option;
        if(option == '1')
            addNew(*cart);
    }
}

/**
 * @brief 添加新商品
 * @details 处理添加新商品的流程：
 * 1. 获取商品基本信息（名称、描述、价格）
 * 2. 选择商品分类
 * 3. 设置商品库存
 * 4. 将商品添加到商品列表
 */
void addNewGoods()
{
    string name, desc;
    Category category;
    double price;
    int storage, tmp;
    
    // 获取商品基本信息
    cout << "please input name:\t";
    cin >> name;
    cout << "description about this goods:\t";
    cin >> desc;
    cout << "price per item:\t";
    cin >> price;

    // 选择商品分类
CATEGORY_INPUT:
    cout << "\n1. home"         // 家居用品
         << "\n2. food"         // 食品
         << "\n3. cloth"        // 服装
         << "\n4. baby care"    // 婴儿用品
         << "\ncategory of this goods:\t";
    cin >> tmp;
    switch (tmp)
    {
    case 1:
        category = home;
        break;
    case 2:
        category = food;
        break;
    case 3:
        category = cloth;
        break;
    case 4:
        category = baby_care;
        break;
    default:
        cout << "wrong input! Please input again:";
        goto CATEGORY_INPUT;
        break;
    }

    // 设置商品库存
    cout << "storage remain:\t";
    cin >> storage;

    // 添加商品到商品列表
    if (goods_list->addGoods(name, desc, category, price, storage))
        cout << "\nadd goods success!";
    else
        cout << "\n this kind of goods has existed!";
}

/**
 * @brief 更新商品信息
 * @details 处理更新商品信息的流程：
 * 1. 查找要更新的商品
 * 2. 获取新的商品信息
 * 3. 更新商品信息
 */
void updateGoods()
{
    string goodsNameOld, goodsNameNew, desc;
    Category category;
    double price;
    int storage;

    Goods *update;

    // 查找要更新的商品
    cout << "Enter the name of the goods to update: ";
    cin >> goodsNameOld;
    if (goods_list->findGoodsByName(goodsNameOld).empty())
    {
        cout << "\nthis goods does not exist!";
        return;
    }

    // 获取新的商品信息
    cout << "Enter new name: ";
    cin >> goodsNameNew;
    cout << "Enter new description: ";
    cin >> desc;
    cout << "Enter new price: ";
    cin >> price;

    // 选择新的商品分类
CATEGORY_INPUT:
    cout << "\n1. home"         // 家居用品
         << "\n2. food"         // 食品
         << "\n3. cloth"        // 服装
         << "\n4. baby care"    // 婴儿用品
         << "\nEnter new category: ";
    int tmp;
    cin >> tmp;
    switch (tmp)
    {
    case 1:
        category = home;
        break;
    case 2:
        category = food;
        break;
    case 3:
        category = cloth;
        break;
    case 4:
        category = baby_care;
        break;
    default:
        cout << "Wrong input! Please input again:";
        goto CATEGORY_INPUT;
        break;
    }

    // 设置新的库存数量
    cout << "Enter new storage: ";
    cin >> storage;

    // 创建新的商品对象并更新
    update = new Goods(goodsNameNew, desc, category, price, storage, false, 0.0);
    goods_list->updateGoods(goodsNameOld, *update);

    cout << "\nGoods updated successfully!";
}

/**
 * @brief 删除商品
 * @details 处理删除商品的流程：
 * 1. 获取要删除的商品名称
 * 2. 从商品列表中删除商品
 */
void deleteGoods()
{
    string name;
    cout << "\nPlease input the name of goods:\t";
    cin >> name;
    if (goods_list->deleteGoods(name))
    {
        cout << "delete success";
        return;
    }
    cout << "goods does not find!";
}

/**
 * @brief 搜索商品
 * @details 提供多种搜索方式：
 * 1. 按名称搜索
 * 2. 按描述搜索
 * 3. 按分类搜索
 * 4. 按价格搜索
 * 5. 按库存搜索
 * 
 * 显示搜索结果，包括商品的详细信息
 */
void searchGoods()
{
    int tmp;
    string str;
    Category category;
    int store;
    double price;
    vector<Goods*> result;

    // 显示搜索选项
    cout << "\n0. name"           // 按名称搜索
         << "\n1. descipsion"     // 按描述搜索
         << "\n2. category"       // 按分类搜索
         << "\n3. price"          // 按价格搜索
         << "\n4. storage"        // 按库存搜索
         << "\nenter a type that you wanna search:\t";
    cin >> tmp;

    // 根据选择执行相应的搜索
    switch (tmp)
    {
    case 0:  // 按名称搜索
        cout << "enter the name:\t";
        cin >> str;
        result = goods_list->findGoodsByName(str);
        break;
    case 1:  // 按描述搜索
        cout << "enter the description:\t";
        cin >> str;
        result = goods_list->findGoodsByDesc(str);
        break;
    case 2:  // 按分类搜索
    CATEGORY_INPUT:
        cout << "\n1. home"         // 家居用品
             << "\n2. food"         // 食品
             << "\n3. cloth"        // 服装
             << "\n4. baby care"    // 婴儿用品
             << "\nEnter the category:\t";
        int tmp;
        cin >> tmp;
        switch (tmp)
        {
        case 1:
            category = home;
            break;
        case 2:
            category = food;
            break;
        case 3:
            category = cloth;
            break;
        case 4:
            category = baby_care;
            break;
        default:
            cout << "Wrong input! Please input again:";
            goto CATEGORY_INPUT;
            break;
        }
        result = goods_list->findGoodsByCategory(category);
        break;
    case 3:  // 按价格搜索
        cout << "enter the price:\t";
        cin >> price;
        result = goods_list->findGoodsByPrice(price);
        break;
    case 4:  // 按库存搜索
        cout << "enter the storage:\t";
        cin >> store;
        result = goods_list->findGoodsByStorage(store);
        break;
    default:  // 无效选择
        cout << "enter a wrong code!";
        break;
    }

    // 显示搜索结果
    cout << "\nthe search result:";
    for (auto it = result.begin(); it != result.end(); ++it)
        cout << "\nname:\t" << (*it)->getName()
             << "\tdescription:\t" << (*it)->getDesc()
             << "\tprice:\t" << (*it)->getPrice()
             << "\tcategory:\t" << (*it)->getCategory()
             << "\tstorage:\t" << (*it)->getStorage() << "\n";
}
