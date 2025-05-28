#include "../include/header.hpp"
using namespace std;

User::User() : username(""), password(""), role(customer), userCart(), orders() {}
User::User(string name, string pwd, Role r) : username(name), password(pwd), role(r) {}
User::User(string name, string pwd, Role r, Cart cart, Order order) : username(name), password(pwd), role(r), userCart(cart), orders(order) {}
User::User(string name, string pwd, Role r, Cart cart, Order order, bool isDiscounted, unordered_map<int, int> &discountList) : username(name), password(pwd), role(r), userCart(cart), orders(order), isDisCount(isDiscounted), disCountList(discountList) {}

string User::getUsername() const { return username; }

void User::setUsername(const string &name) { username = name; }

string User::getPassword() const { return password; }

void User::setPassword(const string &pwd) { password = pwd; }

Role User::getRole() const { return role; }

void User::setRole(Role r) { role = r; }

void User::setRole(string role) { 
    if (role == "admin") {
        this->role = admin;
    } else {
        this->role = customer;
    }
 }

Cart &User::getCart() { return userCart; }

Order &User::getUserOrder() { return orders; }

bool User::getIsDiscounted() const { return isDisCount; }

void User::setIsDiscounted(bool isDiscounted) { isDisCount = isDiscounted; }

unordered_map<int, int> User::getDiscountList() const { return disCountList; }

void User::setCart(Cart &cart) { userCart = cart; }

void User::setUserOrder(Order &order) { orders = order; }

void User::setDiscountList(unordered_map<int, int> &discountList) { disCountList = discountList; }

bool User::addDiscount(int discount, int limit)
{
    for (auto &item : disCountList)
    {
        if (item.first == discount && item.second == limit)
            return false;
    }
    disCountList[discount] = limit;
    return true;
}

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

unordered_map<string, User> UserList::getUserList() const { return userList; }

vector<User*> UserList::findUserByUsername(const string &username) const
{
    vector<User*> result;
    auto it = userList.find(username);
    if (it != userList.end())
        result.push_back(const_cast<User*>(&(it->second)));
    return result;
}

void UserList::iterateUsers() const
{
    for (auto pair : userList)
    {
        cout << "Username: " << pair.first
             << ", Role: " << (pair.second.getRole() == admin ? "Admin" : "Customer") << "\n"
             << "Password: " << pair.second.getPassword() << "\n";
        for(auto &item : pair.second.getCart().getItems())
        {
            cout << "Item: " << item.goods->getName()
                 << ", Quantity: " << item.quantity
                 << ", Status: " << item.status << "\n";
        }
        for(auto &item : pair.second.getUserOrder().getItems())
        {
            cout << "Item: " << item.goods->getName()
                 << ", Quantity: " << item.quantity
                 << ", Status: " << item.status << "\n";
        }
        cout << "Discount List: ";
        for(auto &item : pair.second.getDiscountList())
        {
            cout << "Spend " << item.first << " get " << item.second << " off\n";
        }
        cout << "----------------------------------------\n";
    }
}

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

bool UserList::deleteUser(const string &username)
{
    bool result = userList.erase(username) > 0;
    if (result) {
        writeToFile();  // 同步到文件
    }
    return result;
}

bool UserList::addUser(const string &username, const string &password, Role role)
{
    if (userList.find(username) != userList.end())
    {
        return false;
    }
    userList[username] = User(username, password, role);
    writeToFile();  // 同步到文件
    return true;
}

bool UserList::addUser(User user)
{
    if (userList.find(user.getUsername()) != userList.end())
    {
        return false;
    }
    userList[user.getUsername()] = user;
    writeToFile();  // 同步到文件
    return true;
}

bool UserList::updateUser(const string &username, const User &newUser)
{
    auto it = userList.find(username);
    if (it != userList.end())
    {
        User updatedUser = newUser;
        userList.erase(it);
        userList[updatedUser.getUsername()] = updatedUser;
        writeToFile();  // 同步到文件
        return true;
    }
    return false;
}
