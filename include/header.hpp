#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdlib.h>

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

class Goods;

class User
{
private:
    string username;
    string password;
    Role role;
    vector<Goods> cart;
public:
    User();
    User(string name, string pwd, Role r);

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

    vector<User> findUserByUsername(const string &username) const;

    void iterateUsers() const;

    vector<User> findUsersByRole(Role role) const;

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

    vector<Goods> findGoodsByName(const string &name) const;
    vector<Goods> findGoodsByDesc(const string &desc) const;
    vector<Goods> findGoodsByCategory(Category category) const;
    vector<Goods> findGoodsByPrice(double price) const;
    vector<Goods> findGoodsByStorage(int storage) const;
    void iterateGoods() const;    
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

void changePassword(User *user);
void listAllUsers();
void updateUser();

void listAllGoods();
void addNewGoods();
void updateGoods();
void deleteGoods();
void searchGoods();

#endif