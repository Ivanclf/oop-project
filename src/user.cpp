/**
 * @file user.cpp
 * @brief 用户模块实现
 * @details 实现了用户类和用户列表类的所有方法，包括用户的增删改查、购物车管理、订单管理等功能
 */

#include "../include/header.hpp"
using namespace std;
extern bool fileInit;  // 文件初始化状态标志

/**
 * @brief 用户类默认构造函数
 * @details 初始化一个空用户，所有属性设置为默认值
 */
User::User() : username(""), password(""), role(customer), userCart(), orders() {}

/**
 * @brief 用户类构造函数（基本属性）
 * @param name 用户名
 * @param pwd 密码
 * @param r 用户角色
 */
User::User(string name, string pwd, Role r) : username(name), password(pwd), role(r) {}

/**
 * @brief 用户类构造函数（带购物车和订单）
 * @param name 用户名
 * @param pwd 密码
 * @param r 用户角色
 * @param cart 购物车
 * @param order 订单
 */
User::User(string name, string pwd, Role r, Cart cart, Order order) 
    : username(name), password(pwd), role(r), userCart(cart), orders(order) {}

/**
 * @brief 用户类构造函数（完整属性）
 * @param name 用户名
 * @param pwd 密码
 * @param r 用户角色
 * @param cart 购物车
 * @param order 订单
 * @param isDiscounted 是否享受折扣
 * @param discountList 折扣列表
 */
User::User(string name, string pwd, Role r, Cart cart, Order order, 
    bool isDiscounted, unordered_map<int, int> &discountList) 
    : username(name), password(pwd), role(r), userCart(cart), orders(order), 
    isDisCount(isDiscounted), disCountList(discountList) {}

// 用户基本属性的getter和setter方法
string User::getUsername() const { return username; }
void User::setUsername(const string &name) { username = name; }

string User::getPassword() const { return password; }
void User::setPassword(const string &pwd) { password = pwd; }

Role User::getRole() const { return role; }
void User::setRole(Role r) { role = r; }

/**
 * @brief 通过字符串设置用户角色
 * @param role 角色字符串（"0":管理员, 其他:顾客）
 */
void User::setRole(string role)
{
    if (role == "0")
    {
        this->role = admin;
    }
    else
    {
        this->role = customer;
    }
}

// 购物车和订单相关方法
Cart &User::getCart() { return userCart; }
Order &User::getUserOrder() { return orders; }
void User::setCart(Cart &cart) { userCart = cart; }
void User::setUserOrder(Order &order) { orders = order; }

// 折扣相关方法
bool User::getIsDiscounted() const { return isDisCount; }
void User::setIsDiscounted(bool isDiscounted) { isDisCount = isDiscounted; }
unordered_map<int, int> User::getDiscountList() const { return disCountList; }
void User::setDiscountList(unordered_map<int, int> &discountList) { disCountList = discountList; }

/**
 * @brief 添加折扣规则
 * @param discount 折扣金额
 * @param limit 消费限额
 * @return bool 添加成功返回true，否则返回false
 */
bool User::addDiscount(int discount, int limit)
{
    // 检查是否已存在相同的折扣规则
    for (auto &item : disCountList)
    {
        if (item.first == discount && item.second == limit)
            return false;
    }
    disCountList[discount] = limit;
    return true;
}

/**
 * @brief 删除折扣规则
 * @param discount 折扣金额
 * @param quantity 消费限额
 * @return bool 删除成功返回true，否则返回false
 */
bool User::deleteDiscount(int discount, int quantity)
{
    for (auto it = disCountList.begin(); it != disCountList.end(); ++it)
    {
        if (it->first == discount && it->second == quantity)
        {
            disCountList.erase(it);
            return true;
        }
    }
    return false;
}

/**
 * @brief 获取用户列表
 * @return unordered_map<string, User> 返回所有用户的映射表
 */
unordered_map<string, User> UserList::getUserList() const { return userList; }

/**
 * @brief 根据用户名查找用户
 * @param username 用户名
 * @return vector<User*> 返回匹配用户的指针列表
 */
vector<User *> UserList::findUserByUsername(const string &username) const
{
    vector<User *> result;
    auto it = userList.find(username);
    if (it != userList.end())
        result.push_back(const_cast<User *>(&(it->second)));
    return result;
}

/**
 * @brief 遍历并显示所有用户信息
 * @details 显示每个用户的：
 * - 用户名和角色
 * - 密码
 * - 购物车中的商品
 * - 订单中的商品
 * - 折扣规则列表
 */
void UserList::iterateUsers() const
{
    if (userList.empty())
    {
        cout << "No users" << endl;
        return;
    }
    for (auto pair : userList)
    {
        // 显示用户基本信息
        cout << "Username: " << pair.first
             << ", Role: " << (pair.second.getRole() == admin ? "Admin" : "Customer") << "\n"
             << "Password: " << pair.second.getPassword() << "\n";
        
        // 显示购物车信息
        for (auto &item : pair.second.getCart().getItems())
        {
            cout << "Item: " << item.goods->getName()
                 << ", Quantity: " << item.quantity
                 << ", Status: " << item.status << "\n";
        }
        
        // 显示订单信息
        for (auto &item : pair.second.getUserOrder().getItems())
        {
            cout << "Item: " << item.goods->getName()
                 << ", Quantity: " << item.quantity
                 << ", Status: " << item.status << "\n";
        }
        
        // 显示折扣信息
        cout << "Discount List: ";
        for (auto &item : pair.second.getDiscountList())
        {
            cout << "Spend " << item.first << " get " << item.second << " off\n";
        }
        cout << "----------------------------------------\n";
    }
}

/**
 * @brief 根据角色查找用户
 * @param role 用户角色
 * @return vector<User> 返回匹配用户的列表
 */
vector<User> UserList::findUsersByRole(Role role) const
{
    vector<User> result;
    for (const auto &pair : userList)
    {
        if (pair.second.getRole() == role)
        {
            result.push_back(pair.second);
        }
    }
    return result;
}

/**
 * @brief 删除用户
 * @param username 要删除的用户名
 * @return bool 删除成功返回true，否则返回false
 */
bool UserList::deleteUser(const string &username)
{
    bool result = userList.erase(username) > 0;
    if (result && fileInit)
    {
        writeToFile();  // 同步到文件
    }
    return result;
}

/**
 * @brief 添加用户（基本属性）
 * @param username 用户名
 * @param password 密码
 * @param role 用户角色
 * @return bool 添加成功返回true，否则返回false
 */
bool UserList::addUser(const string &username, const string &password, Role role)
{
    if (userList.find(username) != userList.end())
    {
        return false;  // 用户已存在
    }
    userList[username] = User(username, password, role);
    if (fileInit)
        writeToFile();  // 同步到文件
    return true;
}

/**
 * @brief 添加用户对象
 * @param user 要添加的用户对象
 * @return bool 添加成功返回true，否则返回false
 */
bool UserList::addUser(User user)
{
    if (userList.find(user.getUsername()) != userList.end())
        return false;  // 用户已存在
    userList[user.getUsername()] = user;
    if (fileInit)
        writeToFile();  // 同步到文件
    return true;
}

/**
 * @brief 更新用户信息
 * @param username 要更新的用户名
 * @param newUser 新的用户信息
 * @return bool 更新成功返回true，否则返回false
 */
bool UserList::updateUser(const string &username, const User &newUser)
{
    auto it = userList.find(username);
    if (it != userList.end())
    {
        User updatedUser = newUser;
        userList.erase(it);
        userList[updatedUser.getUsername()] = updatedUser;
        if (fileInit)
            writeToFile();  // 同步到文件
        return true;
    }
    return false;
}
