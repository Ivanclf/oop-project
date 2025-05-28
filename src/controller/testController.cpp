#include "../../include/header.hpp"
using namespace std;
extern GoodsList *goods_list;
extern UserList *user_list;

void testController()
{
    auto test = user_list->findUserByUsername("d").back();
    Goods testGoods1 = *(goods_list->findGoodsByName("eggs").back());
    Goods testGoods2 = *(goods_list->findGoodsByName("apple").back());
    Goods testGoods3 = *(goods_list->findGoodsByName("shampoo").back());
    string name1 = testGoods1.getName();
    string name2 = testGoods2.getName();
    string name3 = testGoods3.getName();
    test->getCart().addItem(name1, 12);
    test->getCart().addItem(name2, 5);
    test->getCart().addItem(name3, 2);
    writeToFile();
}

void printEnter() { cout << "\n"; }