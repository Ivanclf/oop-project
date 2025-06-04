/**
 * @file testController.cpp
 * @brief 测试控制器模块
 * @details 实现了系统测试相关的功能，用于验证系统的基本功能是否正常
 */

#include "../../include/header.hpp"
using namespace std;

// 外部全局变量声明
extern GoodsList *goods_list;    // 商品列表指针
extern UserList *user_list;      // 用户列表指针

/**
 * @brief 测试控制器函数
 * @details 执行系统基本功能测试，包括：
 * 1. 查找测试用户
 * 2. 查找测试商品
 * 3. 向测试用户的购物车添加商品
 * 4. 保存测试数据到文件
 * 
 * 测试数据包括：
 * - 测试用户："d"
 * - 测试商品：鸡蛋、苹果、洗发水
 * - 测试数量：12个鸡蛋、5个苹果、2瓶洗发水
 */
void testController()
{
    // 获取测试用户
    auto test = user_list->findUserByUsername("d").back();
    
    // 获取测试商品
    Goods testGoods1 = *(goods_list->findGoodsByName("eggs").back());    // 鸡蛋
    Goods testGoods2 = *(goods_list->findGoodsByName("apple").back());   // 苹果
    Goods testGoods3 = *(goods_list->findGoodsByName("shampoo").back()); // 洗发水
    
    // 获取商品名称
    string name1 = testGoods1.getName();
    string name2 = testGoods2.getName();
    string name3 = testGoods3.getName();
    
    // 向测试用户的购物车添加商品
    test->getCart().addItem(name1, 12);  // 添加12个鸡蛋
    test->getCart().addItem(name2, 5);   // 添加5个苹果
    test->getCart().addItem(name3, 2);   // 添加2瓶洗发水
    
    // 保存测试数据
    writeToFile();
}

/**
 * @brief 打印空行
 * @details 用于在控制台输出中创建视觉分隔
 */
void printEnter() { cout << "\n"; }