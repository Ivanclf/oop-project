#include "../include/header.hpp"
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

extern UserList *user_list;
extern GoodsList *goods_list;

void __init__() {

    if(fs::exists(ROOT_DIR + "lib/" + USER_FILE) && fs::exists(ROOT_DIR + "lib/" + GOODS_FILE)) {
        cout << "Reading from file..." << endl;
        readFromFile();
    } else {
        cout << "No file found, creating default data..." << endl;
        vector<Goods> goods = {
            Goods("eggs", "the_cheapest!", Category::food, 9.99, 50, true, 0.9),
            Goods("eggplant", "fresh_now", Category::food, 5.68, 100, true, 0.9),
            Goods("apple", "import_from_China", Category::food, 10.58, 300, true, 0.9),
            Goods("shampoo", "keep_your_hair_clean!", Category::cloth, 25, 200, true, 0.5),
            Goods("jacket", "same_as_Huang_renxun", Category::cloth, 362.8, 5, true, 0.7),
            Goods("toddlering_vehicle", "absolutely_safe!", Category::baby_care, 400, 5, true, 0.8)
        };
        for (auto& g : goods) {
            goods_list->addGoods(g);
        }
        unordered_map<int, int> discounts = {{100, 10}, {200, 15}, {300, 20}};
        vector<User> users = {
            User("admin", "123456", Role::admin),
            User("xiaoming", "123456", Role::customer),
            User("haohao", "88888888", Role::customer),
            User("d", "2", Role::customer, Cart(), Order(), true, discounts)
        };
        for (auto& u : users) {
            user_list->addUser(u);
        }
        writeToFile();
    }
}