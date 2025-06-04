/**
 * @file init.cpp
 * @brief 系统初始化模块
 * @details 负责系统启动时的初始化工作，包括数据文件的检查和创建，以及默认数据的初始化
 */

#include "../include/header.hpp"
using namespace std;

// 外部全局变量声明
extern UserList *user_list;      // 用户列表指针
extern GoodsList *goods_list;    // 商品列表指针
extern const string ROOT_DIR;    // 系统根目录
extern const string USER_FILE;   // 用户数据文件名
extern const string GOODS_FILE;  // 商品数据文件名
extern bool fileInit;            // 文件初始化状态标志

/**
 * @brief 系统初始化函数
 * @details 在系统启动时执行，主要完成以下工作：
 * 1. 检查用户数据和商品数据文件是否存在
 * 2. 如果文件存在，则从文件读取数据
 * 3. 如果文件不存在，则创建默认数据并写入文件
 * 
 * 默认数据包括：
 * - 6种预设商品（食品、服装、母婴用品等类别）
 * - 4个预设用户（1个管理员和3个普通用户）
 * - 预设的折扣方案
 */
void __init__() {
    // 检查数据文件是否存在
    ifstream userFile(ROOT_DIR + "lib/" + USER_FILE, ios::in);
    ifstream goodsFile(ROOT_DIR + "lib/" + GOODS_FILE, ios::in);
    bool userExists = userFile.is_open();
    bool goodsExists = goodsFile.is_open();
    userFile.close();
    goodsFile.close();

    fileInit = false;  // 重置文件初始化状态

    if(userExists && goodsExists) {
        // 如果数据文件存在，从文件读取数据
        cout << "Reading from file..." << endl;
        readFromFile();
        fileInit = true;
    } else {
        // 如果数据文件不存在，创建默认数据
        cout << "No file found, creating default data..." << endl;
        
        // 创建默认商品列表
        vector<Goods> goods = {
            Goods("eggs", "the_cheapest!", Category::food, 9.99, 50, true, 0.9),      // 鸡蛋
            Goods("eggplant", "fresh_now", Category::food, 5.68, 100, true, 0.9),     // 茄子
            Goods("apple", "import_from_China", Category::food, 10.58, 300, true, 0.9),// 苹果
            Goods("shampoo", "keep_your_hair_clean!", Category::cloth, 25, 200, true, 0.5),    // 洗发水
            Goods("jacket", "same_as_Huang_renxun", Category::cloth, 362.8, 5, true, 0.7),     // 夹克
            Goods("toddlering_vehicle", "absolutely_safe!", Category::baby_care, 400, 5, true, 0.8)  // 婴儿车
        };
        
        // 将默认商品添加到商品列表
        for (auto& g : goods) {
            goods_list->addGoods(g);
        }

        // 创建默认折扣方案
        unordered_map<int, int> discounts = {
            {100, 10},  // 满100减10
            {200, 15},  // 满200减15
            {300, 20}   // 满300减20
        };

        // 创建默认用户列表
        vector<User> users = {
            User("admin", "123456", Role::admin),                    // 管理员账户
            User("xiaoming", "123456", Role::customer),              // 普通用户1
            User("haohao", "88888888", Role::customer),              // 普通用户2
            User("d", "2", Role::customer, Cart(), Order(), true, discounts)  // 带折扣的普通用户
        };

        // 将默认用户添加到用户列表
        for (auto& u : users) {
            user_list->addUser(u);
        }

        fileInit = true;  // 设置文件初始化完成标志
        writeToFile();    // 将默认数据写入文件
    }
}