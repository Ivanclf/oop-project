#include "../include/header.hpp"
using namespace std;
extern UserList *user_list;
extern GoodsList *goods_list;
void __init__()
{
    unordered_map<int, int> empty_map;
    unordered_map<int, int> d_map = {{100, 10}, {200, 15}, {300, 20}};
    User admin("admin", "123456", Role::admin, Cart(), Order(), false, empty_map);
    User xiaoming("xiaoming", "123456", Role::customer, Cart(), Order(), false, empty_map);
    User haohao("haohao", "88888888", Role::customer, Cart(), Order(), false, empty_map);
    User d("d", "2", Role::customer, Cart(), Order(), true, d_map);
    user_list->addUser(admin);
    user_list->addUser(xiaoming); 
    user_list->addUser(haohao);
    user_list->addUser(d);

    Goods eggs("eggs", "the cheapest!", food, 9.99, 50, true, 0.9);
    Goods shampoo("shampoo", "keep your hair clean!", home, 25, 200, true, 0.5);
    Goods jacket("jacket", "same as Huang renxun", cloth, 362.8, 5, true, 0.7);
    Goods vehicle("toddlering vehicle", "absolutely safe!", baby_care, 400, 5, true, 0.8);
    Goods eggplant("eggplant", "fresh now", food, 5.68, 100, true, 0.9);
    Goods apple("apple", "import from China", food, 10.58, 300, true, 0.9);
    goods_list->addGoods(eggs);
    goods_list->addGoods(shampoo);
    goods_list->addGoods(jacket);
    goods_list->addGoods(vehicle);
    goods_list->addGoods(eggplant);
    goods_list->addGoods(apple);
}