#include "../include/header.hpp"
using namespace std;
extern UserList *user_list;
extern GoodsList *goods_list;
void __init__()
{
    user_list->addUser(*(new User("admin", "123456", admin)));
    user_list->addUser(*(new User("xiaoming", "123456", customer)));
    user_list->addUser(*(new User("haohao", "88888888", customer)));
    user_list->addUser(*(new User("d", "2", customer, true, {{0.9, 10}, {0.8, 20}, {0.7, 30}})));

    goods_list->addGoods(*(new Goods("eggs", "the cheapest!", food, 9.99, 50, true, 0.9)));
    goods_list->addGoods(*(new Goods("shampoo", "keep your hair clean!", home, 25, 200, true, 0.5)));
    goods_list->addGoods(*(new Goods("jacket", "same as Huang renxun", cloth, 362.8, 5, true, 0.7)));
    goods_list->addGoods(*(new Goods("toddlering vehicle", "absolutely safe!", baby_care, 400, 5, true, 0.8)));
    goods_list->addGoods(*(new Goods("eggplant", "fresh now", food, 5.68, 100, true, 0.9)));
    goods_list->addGoods(*(new Goods("apple", "import from China", food, 10.58, 300, true, 0.9)));
}