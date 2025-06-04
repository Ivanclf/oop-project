/**
 * @file main.cpp
 * @brief 电商系统主程序入口
 * @details 包含系统全局变量的定义和主函数的实现
 * @author 系统开发团队
 */

#include "../include/header.hpp"

// 全局变量定义
UserList *user_list = new UserList();    // 用户列表全局指针，管理所有用户信息
GoodsList *goods_list = new GoodsList(); // 商品列表全局指针，管理所有商品信息

// 系统文件路径配置
const string ROOT_DIR = "/home/kylin/桌面/oop/";  // 系统根目录路径
const string USER_FILE = "user_list.txt";         // 用户数据文件路径
const string GOODS_FILE = "goods_list.txt";       // 商品数据文件路径

bool fileInit = false;  // 文件初始化标志，用于标记系统数据文件是否已初始化

/**
 * @brief 主函数
 * @details 系统入口点，负责初始化系统、运行测试控制器和启动登录流程
 * @return int 返回登录控制器的执行结果，用于指示程序退出状态
 */
int main()
{
    __init__();         // 系统初始化，包括数据文件检查和创建
    testController();   // 运行系统测试控制器
    return loginController();  // 启动登录流程并返回执行结果
}
