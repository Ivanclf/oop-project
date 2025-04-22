#include "../../include/header.hpp"
using namespace std;

extern UserList *user_list;
extern GoodsList *goods_list;

void listAllGoods() { goods_list->iterateGoods(); }

void addNewGoods()
{
    string name, desc;
    Category category;
    double price;
    int storage, tmp;
    cout << "please input name:\t";
    cin >> name;
    cout << "description about this goods:\t";
    cin >> desc;
    cout << "price per item:\t";
    cin >> price;
CATEGORY_INPUT:
    cout << "\n1. home"
         << "\n2. food"
         << "\n3. cloth"
         << "\nbaby care"
         << "\ncategory of this goods:\t";
    cin >> tmp;
    switch (tmp)
    {
    case 1:
        category = home;
        break;
    case 2:
        category = food;
        break;
    case 3:
        category = cloth;
        break;
    case 4:
        category = baby_care;
        break;
    default:
        cout << "wrong input! Please input again:";
        goto CATEGORY_INPUT;
    }
    cin >> price;
    cout << "storage remain:\t";
    cin >> storage;
    if (goods_list->addGoods(name, desc, category, price, storage))
    {
        cout << "\nadd goods success!";
    }
    else
    {
        cout << "\n this kind odf goods has existed!";
    }
}

void updateGoods()
{
    string goodsNameOld, goodsNameNew, desc;
    Category category;
    double price;
    int storage;

    Goods *update;

    cout << "Enter the name of the goods to update: ";
    cin >> goodsNameOld;
    if (goods_list->findGoodsByName(goodsNameNew).empty())
    {
        cout << "\nthis goods does not exist!";
        return;
    }

    cout << "Enter new name: ";
    cin >> goodsNameNew;
    cout << "Enter new description: ";
    cin >> desc;
    cout << "Enter new price: ";
    cin >> price;
CATEGORY_INPUT:
    cout << "\n1. home"
         << "\n2. food"
         << "\n3. cloth"
         << "\nbaby care"
         << "\nEnter new category: ";
    int tmp;
    cin >> tmp;
    switch (tmp)
    {
    case 1:
        category = home;
        break;
    case 2:
        category = food;
        break;
    case 3:
        category = cloth;
        break;
    case 4:
        category = baby_care;
        break;
    default:
        cout << "Wrong input! Please input again:";
        goto CATEGORY_INPUT;
    }
    cout << "Enter new storage: ";
    cin >> storage;

    update = new Goods(goodsNameNew, desc, category, price, storage);
    goods_list->updateGoods(goodsNameOld, *update);

    cout << "\nGoods updated successfully!";
}

void deleteGoods()
{
    string name;
    cout << "\nPlease input the name of goods:\t";
    cin >> name;
    if (goods_list->findGoodsByName(name).empty())
    {
        cout << "goods does not find!";
        return;
    }
    goods_list->getGoodsList().erase(name);
    cout << "delete success";
}

void searchGoods()
{
    int tmp;
    string str;
    Category category;
    int store;
    double price;
    vector<Goods> result;
    cout << "\n0. name"
         << "\n1. descipsion"
         << "\n2. category"
         << "\n3. price"
         << "\n4. storage"
         << "\nenter a type that you wanna search:\t";
    cin >> tmp;

    switch (tmp)
    {
    case 0:
        cout << "enter the name:\t";
        cin >> str;
        result = goods_list->findGoodsByName(str);
        break;
    case 1:
        cout << "enter the description:\t";
        cin >> str;
        result = goods_list->findGoods(str, 1);
        break;
    case 2:
    CATEGORY_INPUT:
        cout << "\n1. home"
             << "\n2. food"
             << "\n3. cloth"
             << "\nbaby care"
             << "\nEnter the category:\t";
        int tmp;
        cin >> tmp;
        switch (tmp)
        {
        case 1:
            category = home;
            break;
        case 2:
            category = food;
            break;
        case 3:
            category = cloth;
            break;
        case 4:
            category = baby_care;
            break;
        default:
            cout << "Wrong input! Please input again:";
            goto CATEGORY_INPUT;
        }
        result = goods_list->findGoods(category, 2);
        break;
    case 3:
        cout << "enter the price:\t";
        cin >> price;
        result = goods_list->findGoods(price, 3);
        break;
    case 4:
        cout << "enter the storage:\t";
        cin >> store;
        result = goods_list->findGoods(store, 4);
        break;
    default:
        cout << "enter a wrong code!";
        break;
    }
}