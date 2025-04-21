#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

enum Role
{
    admin,
    customer
};

enum Category
{
    home,
    food,
    cloth,
    baby_care
};

typedef struct userData
{
    string username;
    string password;
    Role role;

    userData() : username("unnamed"), password(""), role(Role::customer) {}
    userData(string uname, string pwd, Role r) : username(uname), password(pwd), role(r) {}
} userData;

class User
{
private:
    userData user_data;

public:
    User();
    User(string uname, string pwd, Role r);

    userData getUserData() const;

    string getUsername() const;
    void setUsername(const string &uname);

    string getPassword() const;
    void setPassword(const string &pwd);

    Role getRole() const;
    void setRole(Role r);
};

class UserList
{
private:
    unordered_map<string, User> userList;

public:
    unordered_map<string, User> getUserList() const;

    User *findUserByUsername(const string &username);

    void iterateUsers() const;

    vector<string> findUsersByRole(Role role) const;

    bool deleteUser(const string &username);

    bool addUser(const string &username, const string &password, Role role);
    bool addUser(User user);
    bool updateUser(const string &username, const User &newUser);
};

class Goods
{
private:
    string name;
    string desc;
    Category category;
    double price;
    int storage;
public:
    Goods();
    Goods(const string &name, const string &desc, Category category, double price, int storage);

    string getName() const;
    void setName(const string &name);

    string getDesc() const;
    void setDesc(const string &desc);

    Category getCategory() const;
    void setCategory(Category category);

    double getPrice() const;
    void setPrice(double price);

    int getStorage() const;
    void setStorage(int storage);
};

class GoodsList {
private:
    unordered_map<string, Goods> goodsList;
public:
    unordered_map<string, Goods> getGoodsList() const;

    Goods *findGoodsByName(const string &name);

    void iterateGoods() const;

    vector<string> findGoodsByCategory(Category category) const;

    bool deleteGoods(const string &name);

    bool addGoods(const string &name, const string &desc, Category category, double price, int storage);
    bool addGoods(Goods goods);
    bool updateGoods(const string &name, const Goods &newGoods);
};

void __init__();

int loginController();

void loginUser();

User *registerUser();

void adminController(User *user);

void customerController(User *user);

#endif