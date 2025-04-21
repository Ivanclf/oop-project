#include "../include/header.hpp"
using namespace std;
extern UserList *user_list;
void __init__()
{
    user_list->addUser(*(new User("admin", "123456", admin)));
    user_list->addUser(*(new User("xiaoming", "123456", customer)));
    user_list->addUser(*(new User("haohao", "88888888", customer)));
}