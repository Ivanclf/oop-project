/**
 * @file fileController.cpp
 * @brief 文件控制器模块
 * @details 实现了系统数据持久化的主要功能，包括：
 * 1. 用户数据管理（保存、读取用户信息）
 * 2. 商品数据管理（保存、读取商品信息）
 * 3. 购物车数据管理（保存、读取购物车信息）
 * 4. 订单数据管理（保存、读取订单信息）
 * 5. 折扣数据管理（保存、读取折扣信息）
 */

#include "../../include/header.hpp"

// 外部全局变量声明
extern UserList *user_list;    // 用户列表指针
extern GoodsList *goods_list;  // 商品列表指针
extern const string ROOT_DIR;  // 根目录路径
extern const string USER_FILE; // 用户数据文件名
extern const string GOODS_FILE;// 商品数据文件名
extern bool fileInit;          // 文件初始化标志

namespace
{
    /**
     * @brief 验证字符串是否为有效数字
     * @param str 要验证的字符串
     * @return bool 是否为有效数字
     * @details 检查字符串是否符合数字格式：
     * 1. 可以包含正负号
     * 2. 可以包含一个小数点
     * 3. 必须包含至少一个数字
     */
    bool isValidNumber(const string &str)
    {
        if (str.empty())
            return false;
        bool hasDecimal = false;
        bool hasDigit = false;
        for (size_t i = 0; i < str.size(); ++i)
        {
            if (isdigit(str[i]))
            {
                hasDigit = true;
            }
            else if (str[i] == '.')
            {
                if (hasDecimal)
                    return false;
                hasDecimal = true;
            }
            else if (str[i] != '-' && str[i] != '+')
            {
                return false;
            }
        }
        return hasDigit;
    }

    // 注释掉的函数，用于将字符串中的下划线替换为空格
    // void replaceAllUnderscoreWithSpace(string &str)
    // {
    //     for (size_t i = 0; i < str.size(); ++i)
    //     {
    //         if (str[i] == '_')
    //         {
    //             str.replace(i, 1, " ");
    //         }
    //     }
    // }
}

/**
 * @brief 将数据写入文件
 * @details 将系统中的所有数据保存到文件，包括：
 * 1. 用户数据（基本信息、购物车、订单、折扣）
 * 2. 商品数据（基本信息、折扣信息）
 */
void writeToFile()
{
    // 检查文件系统是否初始化
    if (!fileInit)
    {
        cerr << "fail to write\n";
        return;
    }

    // 打开用户和商品数据文件
    ofstream userFile(ROOT_DIR + "lib/" + USER_FILE, ios::out);
    ofstream goodsFile(ROOT_DIR + "lib/" + GOODS_FILE, ios::out);

    // 保存用户数据
    for (auto &user : user_list->getUserList())
    {
        // 保存用户基本信息
        userFile << user.first << " " << user.second.getPassword() << " " << user.second.getRole() << endl;

        // 保存购物车数据
        if (user.second.getCart().getSize() > 0)
        {
            userFile << "cart" << endl;
            for (auto &item : user.second.getCart().getItems())
            {
                userFile << item.goods->getName() << " " << item.quantity << " " << item.status << endl;
            }
            userFile << "cart end" << endl;
        }

        // 保存订单数据
        if (user.second.getUserOrder().getItems().size() > 0)
        {
            userFile << "order" << endl;
            for (auto &item : user.second.getUserOrder().getItems())
            {
                userFile << item.goods->getName() << " " << item.quantity << " " << item.status << endl;
            }
            userFile << "order end" << endl;
        }

        // 保存折扣数据
        if (user.second.getIsDiscounted() && user.second.getDiscountList().size() > 0)
        {
            userFile << "discount" << endl;
            for (auto &item : user.second.getDiscountList())
            {
                userFile << item.first << " " << item.second << endl;
            }
            userFile << "discount end" << endl;
        }
        userFile << endl;
    }
    userFile.close();

    // 保存商品数据
    for (auto &goods : goods_list->getGoodsList())
    {
        // 保存商品基本信息
        goodsFile << goods.first << " " << goods.second.getDesc() << " " 
                 << goods.second.getCategory() << " " << goods.second.getPrice() 
                 << " " << goods.second.getStorage() << endl;

        // 保存商品折扣信息
        if (goods.second.getIsDiscounted() && goods.second.getDiscountScale() != 1.0)
        {
            goodsFile << "discount" << endl;
            goodsFile << goods.second.getDiscountScale() << endl;
            goodsFile << "discount end" << endl;
        }
    }
    goodsFile.close();
}

/**
 * @brief 从文件读取数据
 * @details 从文件中读取所有数据到系统，包括：
 * 1. 商品数据（基本信息、折扣信息）
 * 2. 用户数据（基本信息、购物车、订单、折扣）
 */
void readFromFile()
{
    string line;

    // 读取商品数据
    ifstream goodsFile(ROOT_DIR + "lib/" + GOODS_FILE, ios::in);
    if (!goodsFile.is_open())
    {
        cout << "Failed to open goods file" << endl;
        return;
    }

    // 逐行读取商品数据
    while (getline(goodsFile, line))
    {
        if (line.empty())
            continue;

        Goods goods;
        stringstream goodsIss(line);

        // 解析商品基本信息
        string name, desc, category, price, storage;
        if (goodsIss >> name >> desc >> category >> price >> storage)
        {
            // 检查商品是否已存在
            if (goods_list->findGoodsByName(name).size() > 0)
            {
                while (getline(goodsFile, line) && !line.empty())
                {
                }
                continue;
            }

            // 验证价格和库存数据
            if (!isValidNumber(price) || !isValidNumber(storage))
            {
                cout << "Invalid price or storage for " << name << endl;
                goods.setPrice(0.0);
                goods.setStorage(0);
            }
            else
            {
                goods.setPrice(stod(price));
                goods.setStorage(stoi(storage));
            }

            // 设置商品基本信息
            goods.setDesc(desc);
            goods.setCategory(category);
            goods.setName(name);

            // 读取商品折扣信息
            if (getline(goodsFile, line))
            {
                if (line == "discount")
                {
                    if (getline(goodsFile, line))
                    {
                        if (isValidNumber(line))
                        {
                            goods.setDiscountScale(stod(line));
                            goods.setIsDiscounted(true);
                        }
                        else
                        {
                            cout << "Invalid discount scale for " << name << endl;
                            goods.setDiscountScale(1.0);
                        }
                    }

                    if (getline(goodsFile, line) && line != "discount end")
                        cout << "Missing discount end for " << name << endl;
                }
                else
                    goodsFile.seekg(-(int)line.size() - 1, ios_base::cur);
            }

            // 添加商品到商品列表
            goods_list->addGoods(goods);
        }
    }
    goodsFile.close();

    // 读取用户数据
    ifstream userFile(ROOT_DIR + "lib/" + USER_FILE, ios::in);
    if (!userFile.is_open())
    {
        cout << "Failed to open user file" << endl;
        return;
    }

    // 逐行读取用户数据
    while (getline(userFile, line))
    {
        if (line.empty())
            continue;

        User user;
        stringstream userIss(line);

        // 解析用户基本信息
        string username, password, role;
        if (userIss >> username >> password >> role)
        {
            user.setUsername(username);
            user.setPassword(password);
            user.setRole(role);

            Cart cart;
            Order order;
            unordered_map<int, int> discountList;

            // 读取用户的其他数据
            while (getline(userFile, line))
            {
                if (line.empty())
                    break;

                if (line == "cart")  // 读取购物车数据
                {
                    while (getline(userFile, line) && line != "cart end")
                    {
                        istringstream cartIss(line);
                        string name, quantity, status;
                        if (cartIss >> name >> quantity >> status)
                        {
                            auto goods = goods_list->findGoodsByName(name);
                            if (!goods.empty())
                            {
                                cart.addItem(name, stoi(quantity));
                                cart.getItem(name).status = order_status(stoi(status));
                            }
                        }
                    }
                }
                else if (line == "order")  // 读取订单数据
                {
                    while (getline(userFile, line) && line != "order end")
                    {
                        istringstream orderIss(line);
                        string name, quantity, status;
                        if (orderIss >> name >> quantity >> status)
                        {
                            auto goods = goods_list->findGoodsByName(name);
                            if (!goods.empty())
                            {
                                order.addItem(name, stoi(quantity), order_status(stoi(status)));
                            }
                        }
                    }
                }
                else if (line == "discount")  // 读取折扣数据
                {
                    unordered_map<int, int> tempDiscountList;
                    while (getline(userFile, line) && line != "discount end")
                    {
                        istringstream discountIss(line);
                        int limit, discount;
                        if (discountIss >> limit >> discount)
                            tempDiscountList[limit] = discount;
                    }
                    discountList = tempDiscountList;
                }
                else
                {
                    break;
                    userFile.seekg(-static_cast<int>(line.length()) - 1, ios_base::cur);
                }
            }

            // 设置用户数据
            user.setCart(cart);
            user.setUserOrder(order);
            user.setDiscountList(discountList);
            user_list->addUser(user);
        }
    }
    userFile.close();
}