#include "../include/header.hpp"

UserList *user_list = new UserList();
GoodsList *goods_list = new GoodsList();
const string ROOT_DIR = "/home/kylin/桌面/oop/";
const string USER_FILE = "user_list.txt";
const string GOODS_FILE = "goods_list.txt";
bool fileInit = false;

int main()
{

    __init__();
    testController();
    return loginController();
}
