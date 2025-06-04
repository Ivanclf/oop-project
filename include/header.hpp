/**
 * @file header.hpp
 * @brief 电商系统核心头文件，定义了系统所需的所有数据结构和接口
 * @details 包含用户管理、商品管理、购物车、订单等核心功能的数据结构定义
 */

#ifndef HEADER_HPP
#define HEADER_HPP

// 标准库头文件引入
#include <iostream>      // 输入输出流
#include <string>        // 字符串处理
#include <unordered_map> // 哈希表容器
#include <vector>        // 动态数组容器
#include <algorithm>     // 算法库
#include <stdlib.h>      // 标准库函数
#include <chrono>        // 时间相关功能
#include <fstream>       // 文件操作
#include <sstream>       // 字符串流
#include <filesystem>    // 文件系统操作

using namespace std;

// 全局常量定义
extern const string ROOT_DIR;    // 系统根目录
extern const string USER_FILE;   // 用户数据文件路径
extern const string GOODS_FILE;  // 商品数据文件路径

/**
 * @brief 订单状态枚举
 * @details 定义了订单在整个生命周期中可能的状态
 */
enum order_status
{
    undefined,    // 未定义状态
    unpayed,      // 未支付
    not_delivered,// 未发货
    delivered,    // 已发货
    checked       // 已确认收货
};

/**
 * @brief 商品类别枚举
 * @details 定义了系统中商品的分类
 */
enum Category
{
    home,      // 家居用品
    food,      // 食品
    cloth,     // 服装
    baby_care  // 母婴用品
};

/**
 * @brief 用户角色枚举
 * @details 定义了系统中的用户类型
 */
enum Role
{
    admin,    // 管理员
    customer  // 普通顾客
};

/**
 * @brief 商品类
 * @details 定义了商品的基本属性和操作方法
 */
class Goods
{
private:
    string name;           // 商品名称
    string desc;           // 商品描述
    Category category;     // 商品类别
    double price;          // 商品价格
    int storage;           // 库存数量
    bool isDiscounted;     // 是否打折
    double discountScale;  // 折扣比例
    double discountedPrice;// 折扣后价格

public:
    Goods();
    Goods(const string &name, const string &desc, Category category, double price, int storage, bool isDiscounted = false, double discountScale = 0.0);
    Goods(const string &name, const string &desc, Category category, double price, int storage);

    string getName() const;
    void setName(const string &name);

    string getDesc() const;
    void setDesc(const string &desc);

    Category getCategory() const;
    void setCategory(Category category);
    void setCategory(string category);

    double getPrice() const;
    void setPrice(double price);

    int getStorage() const;
    void setStorage(int storage);

    bool getIsDiscounted() const;
    void setIsDiscounted(bool isDiscounted);

    double getDiscountScale() const;
    void setDiscountScale(double discountScale);

    double getDiscountedPrice() const;
};

/**
 * @brief 商品列表类
 * @details 管理所有商品的集合，提供商品的增删改查功能
 */
class GoodsList
{
private:
    unordered_map<string, Goods> goodsList;

public:
    unordered_map<string, Goods> getGoodsList() const;

    vector<Goods*> findGoodsByName(const string &name) const;
    vector<Goods*> findGoodsByDesc(const string &desc) const;
    vector<Goods*> findGoodsByCategory(Category category) const;
    vector<Goods*> findGoodsByPrice(double price) const;
    vector<Goods*> findGoodsByStorage(int storage) const;
    bool setStorage(const string &name, int decline);
    void iterateGoods() const;
    bool deleteGoods(const string &name);
    bool addGoods(const string &name, const string &desc, Category category, double price, int storage);
    bool addGoods(const string &name, const string &desc, Category category, double price, int storage, bool isDiscounted, double discountScale);
    bool addGoods(Goods goods);
    bool updateGoods(const string &name, const Goods &newGoods);
};

/**
 * @brief 购物车项目结构体
 * @details 定义了购物车中每个商品项的数据结构
 */
typedef struct ITEM
{
    Goods *goods;         // 商品指针
    int quantity;         // 购买数量
    order_status status;  // 订单状态

    // 构造函数
    ITEM() : goods(nullptr), quantity(0), status(undefined) {}
    ITEM(Goods *goods, int quantity, order_status status) : goods(goods), quantity(quantity), status(status) {}
    ITEM(Goods *goods, int quantity) : goods(goods), quantity(quantity), status(undefined) {}
} Item;

/**
 * @brief 购物车类
 * @details 管理用户的购物车，提供商品的添加、删除、修改数量等功能
 */
class Cart
{
private:
    vector<Item> items;
public:
    void iterateGoods() const;
    Item &getItem(string &name);
    vector<Item> &getItems();
    void addItem(string &name, int quantity);
    bool deleteItem(string &name);
    bool changeQuantity(string &name, const int quantity);
    int getSize() const;
};

/**
 * @brief 订单类
 * @details 管理用户的订单信息，包括订单状态管理、商品排序等功能
 */
class Order
{
private:
    vector<Item> orderList;

    void changeStorage();
    string &printStatus(order_status status) const;
public:
    vector<Item> &getItems();
    void sortByName();
    void sortByStatus();
    void iterateGoods() const;
    void iterateGoodsByStatus(order_status filterStatus) const;
    void addItem(string &name, int quantity, order_status status);
    bool deleteItem(string &name);
    bool setItemStatus(const string &itemName, order_status newStatus);
    order_status &getItemStatus(string &itemName);
};

/**
 * @brief 用户类
 * @details 定义了用户的基本信息、购物车、订单等属性，以及相关的操作方法
 */
class User
{
private:
    string username;                           // 用户名
    string password;                           // 密码
    Role role;                                 // 用户角色
    Cart userCart;                             // 用户购物车
    Order orders;                              // 用户订单
    bool isDisCount;                           // 是否享受折扣
    unordered_map<int, int> disCountList;      // 折扣列表（折扣值->使用次数）
public:
    User();
    User(string name, string pwd, Role r);
    User(string name, string pwd, Role r, Cart cart, Order order);
    User(string name, string pwd, Role r, Cart cart, Order order, bool isDiscounted, unordered_map<int, int> &discountList);
    
    string getUsername() const;
    void setUsername(const string &uname);
    
    string getPassword() const;
    void setPassword(const string &pwd);
    
    Role getRole() const;
    void setRole(Role r);
    void setRole(string role);
    

    bool getIsDiscounted() const;
    void setIsDiscounted(bool isDiscounted);

    unordered_map<int, int> getDiscountList() const;
    void setDiscountList(unordered_map<int, int> &discountList);
    bool addDiscount(int discount, int limit);
    bool deleteDiscount(int discount, int quantity);

    Cart &getCart();
    Order &getUserOrder();
    void setCart(Cart &cart);
    void setUserOrder(Order &order);
};

/**
 * @brief 用户列表类
 * @details 管理所有用户信息，提供用户的增删改查功能
 */
class UserList
{
private:
    unordered_map<string, User> userList;
public:
    unordered_map<string, User> getUserList() const;
    vector<User*> findUserByUsername(const string &username) const;
    void iterateUsers() const;
    vector<User> findUsersByRole(Role role) const;
    bool deleteUser(const string &username);
    bool addUser(const string &username, const string &password, Role role);
    bool addUser(User user);
    bool updateUser(const string &username, const User &newUser);
};

// 系统初始化和测试函数
void __init__();           // 系统初始化
void testController();     // 测试控制器
void printEnter();         // 打印分隔线

// 文件操作函数
void writeToFile();        // 将数据写入文件
void readFromFile();       // 从文件读取数据

// 用户认证相关函数
int loginController();     // 登录控制器
void loginUser();          // 用户登录
User registerUser();       // 用户注册

// 用户控制函数
void adminController(User &user);      // 管理员控制器
void customerController(User &user);   // 顾客控制器

// 购物车控制函数
void cartController(Cart &userCart, Order &order);  // 购物车控制器
void addNew(Cart &userCart);                       // 添加新商品到购物车

// 用户管理函数
void changePassword(User &user);       // 修改密码
void listAllUsers();                   // 列出所有用户
void updateUser();                     // 更新用户信息

// 商品管理函数
void listAllGoods(User &user);         // 列出所有商品
void addNewGoods();                    // 添加新商品
void updateGoods();                    // 更新商品信息
void deleteGoods();                    // 删除商品
void searchGoods();                    // 搜索商品

// 订单管理函数
void orderController(Order &orders);           // 订单控制器
void changeOrderStatus(Order &orders);         // 修改订单状态
void change_Order_Status();                    // 更改订单状态
void manageUserOrders();                       // 管理用户订单
void computeDiscount(User &user);              // 计算用户折扣
void changeGoodsDiscount();                    // 修改商品折扣
void changeUserDiscount();                     // 修改用户折扣
void iterateDiscount(User &user);              // 遍历用户折扣信息

#endif