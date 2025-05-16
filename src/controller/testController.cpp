#include "../../include/header.hpp"
using namespace std;
extern GoodsList *goods_list;
extern UserList *user_list;

void testController()
{
    auto test = user_list->findUserByUsername("d").back();
    Goods testGoods1 = *(goods_list->findGoodsByName("eggs").back());
    Goods testGoods2 = *(goods_list->findGoodsByName("apple").back());
    string name1 = testGoods1.getName();
    string name2 = testGoods2.getName();
    test->getCart().addItem(name1, 12);
    test->getCart().iterateGoods();
    printEnter();

    test->getCart().addItem(name2, 5);
    test->getCart().iterateGoods();
    printEnter();

    test->getCart().deleteItem(name1);
    test->getCart().iterateGoods();
    printEnter();

    test->getCart().changeQuantity(name2, 3);
    test->getCart().iterateGoods();
    printEnter();

    test->getUserOrder().addItem(name2, 3, unpayed);
    test->getUserOrder().iterateGoods();
    printEnter();

    test->getUserOrder().addItem(name1, 2, unpayed);
    test->getUserOrder().iterateGoods();
    printEnter();

    test->getUserOrder().deleteItem(name2);
    test->getUserOrder().iterateGoods();
    printEnter();
    
}

void printEnter() { cout << "\n"; }