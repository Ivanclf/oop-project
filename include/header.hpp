#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <thread>
#include <chrono>

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

enum order_status
{
    undefined,
    unpayed,
    not_deliverd,
    deliverd,
    checked
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

typedef struct ITEM
{
    Goods item;
    int quantity;
    order_status status;

    ITEM(Goods item, int quantity) : item(item), quantity(quantity), status(undefined) {}
    ITEM(Goods *goods, int quantity) : item(*goods), quantity(quantity), status(undefined) {}
    ITEM(Goods item, int quantity, order_status status) : item(item), quantity(quantity), status(status) {}
    ITEM(Goods *goods, int quantity, order_status status) : item(*goods), quantity(quantity), status(status) {}
    ITEM() : item({}), quantity(0), status(undefined) {}
} Item;

class Cart
{
private:
    vector<Item> items;
public:
    void iterateGoods() const;
    Item &getItem(const int order);
    vector<Item> &getItems();
    void addItem(Goods *goods);
    void addItem(Item &item);
    bool deleteItem(const int order);
    bool changeQuantity(Item &item, const int quantity);
    int getSize() const;
};

class Order
{
private:
    vector<Item> orderList;
    
    void autoChangeStatus();
    void changeStorage();
public:
    Order();
    Order(const vector<Item> &items);
    vector<Item> getItems() const;
    void sortByName();
    static void sortByStatus(vector<Order> &orders);
    void printAllItems() const;
    void printItemsByStatus(order_status filterStatus) const;
    void addItem(const Item &item);
    void addItem(const vector<Item> &itemList);
    bool deleteItem(const string &itemName);
    bool setItemStatus(const string &itemName, order_status newStatus);
    order_status getItemStatus(const string &itemName) const;
};

class User
{
private:
    string username;
    string password;
    Role role;
    Cart userCart;
    Order orders;

public:
    User();
    User(string name, string pwd, Role r);

    string getUsername() const;
    void setUsername(const string &uname);

    string getPassword() const;
    void setPassword(const string &pwd);

    Role getRole() const;
    void setRole(Role r);

    Cart &getCart();

    Order &getUserOrder();
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

class GoodsList
{
private:
    unordered_map<string, Goods> goodsList;

public:
    unordered_map<string, Goods> getGoodsList() const;

    vector<Goods> findGoodsByName(const string &name) const;
    vector<Goods> findGoodsByDesc(const string &desc) const;
    vector<Goods> findGoodsByCategory(Category category) const;
    vector<Goods> findGoodsByPrice(double price) const;
    vector<Goods> findGoodsByStorage(int storage) const;
    bool setStorage(const string &name, int decline);
    void iterateGoods() const;
    bool deleteGoods(const string &name);
    bool addGoods(const string &name, const string &desc, Category category, double price, int storage);
    bool addGoods(Goods goods);
    bool updateGoods(const string &name, const Goods &newGoods);
};

void __init__();

int loginController();
void loginUser();
User registerUser();

void adminController(User &user);
void customerController(User &user);

void cartController(Cart &userCart, Order &orders);
void addNew(Cart &userCart);

void changePassword(User &user);
void listAllUsers();
void updateUser();

void listAllGoods(User &user);
void addNewGoods();
void updateGoods();
void deleteGoods();
void searchGoods();

void orderController(Order &orders); 

#endif