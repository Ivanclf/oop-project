#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

extern const string ROOT_DIR;
extern const string USER_FILE;
extern const string GOODS_FILE;

enum order_status
{
    undefined,
    unpayed,
    not_delivered,
    delivered,
    checked
};

enum Category
{
    home,
    food,
    cloth,
    baby_care
};

enum Role
{
    admin,
    customer
};

class Goods
{
private:
    string name;
    string desc;
    Category category;
    double price;
    int storage;
    bool isDiscounted;
    double discountScale;
    double discountedPrice;

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

typedef struct ITEM
{
    Goods *goods;
    int quantity;
    order_status status;

    ITEM() : goods(nullptr), quantity(0), status(undefined) {}
    ITEM(Goods *goods, int quantity, order_status status) : goods(goods), quantity(quantity), status(status) {}
    ITEM(Goods *goods, int quantity) : goods(goods), quantity(quantity), status(undefined) {}
} Item;

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

class User
{
private:
    string username;
    string password;
    Role role;
    Cart userCart;
    Order orders;
    bool isDisCount;
    unordered_map<int, int> disCountList;
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

void __init__();
void testController();
void printEnter();


void writeToFile();  
void readFromFile();  

int loginController();
void loginUser();
User registerUser();

void adminController(User &user);
void customerController(User &user);

void cartController(Cart &userCart, Order &order);
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
void changeOrderStatus(Order &orders);
void change_Order_Status();
void manageUserOrders();
void computeDiscount(User &user);
void changeGoodsDiscount();
void changeUserDiscount();

#endif