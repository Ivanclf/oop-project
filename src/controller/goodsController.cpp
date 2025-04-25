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
         << "\n4. baby care"
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
        break;
    }
    cout << "storage remain:\t";
    cin >> storage;
    if (goods_list->addGoods(name, desc, category, price, storage))
        cout << "\nadd goods success!";
    else
        cout << "\n this kind of goods has existed!";
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
         << "\n4. baby care"
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
        break;
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
    if (goods_list->deleteGoods(name))
    {
        cout << "delete success";
        return;
    }
    cout << "goods does not find!";
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
        result = goods_list->findGoodsByDesc(str);
        break;
    case 2:
    CATEGORY_INPUT:
        cout << "\n1. home"
             << "\n2. food"
             << "\n3. cloth"
             << "\n4. baby care"
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
            break;
        }
        result = goods_list->findGoodsByCategory(category);
        break;
    case 3:
        cout << "enter the price:\t";
        cin >> price;
        result = goods_list->findGoodsByPrice(price);
        break;
    case 4:
        cout << "enter the storage:\t";
        cin >> store;
        result = goods_list->findGoodsByStorage(store);
        break;
    default:
        cout << "enter a wrong code!";
        break;
    }
    cout << "\nthe search result:";
    for (auto it = result.begin(); it != result.end(); ++it)
        cout << "\nname:\t" << (*it).getName()
             << "\tdescription:\t" << (*it).getDesc()
             << "\tprice:\t" << (*it).getPrice()
             << "\tcategory:\t" << (*it).getCategory()
             << "\tstorage:\t" << (*it).getStorage() << "\n";
}
