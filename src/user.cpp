#include "../include/header.hpp"
using namespace std;

User::User() : user_data() {}
User::User(string uname, string pwd, Role r) : user_data{uname, pwd, r} {}

userData User::getUserData() const { return user_data; }

string User::getUsername() const { return user_data.username; }

void User::setUsername(const string &uname) { user_data.username = uname; }

string User::getPassword() const { return user_data.password; }

void User::setPassword(const string &pwd) { user_data.password = pwd; }

Role User::getRole() const { return user_data.role; }

void User::setRole(Role r) { user_data.role = r; }


unordered_map<string, User> UserList::getUserList() const { return userList; }

User* UserList::findUserByUsername(const string &username)
{
    auto it = userList.find(username);
    if (it != userList.end())
    {
        return &it->second;
    }
    return nullptr;
}

void UserList::iterateUsers() const
{
    for (const auto &pair : userList)
    {
        cout << "Username: " << pair.first << ", Role: " << (pair.second.getRole() == admin ? "Admin" : "Customer") << endl;
    }
}

vector<string> UserList::findUsersByRole(Role role) const
{
    vector<string> result;
    for (const auto &pair : userList)
    {
        if (pair.second.getRole() == role)
        {
            result.push_back(pair.first);
        }
    }
    return result;
}

bool UserList::deleteUser(const string &username)
{
    return userList.erase(username) > 0;
}

bool UserList::addUser(const string &username, const string &password, Role role)
{
    if (userList.find(username) != userList.end())
    {
        return false;
    }
    userList[username] = User(username, password, role);
    return true;
}

bool UserList::addUser(User user)
{
    if (userList.find(user.getUsername()) != userList.end())
    {
        return false;
    }
    userList[user.getUsername()] = user;
    return true;
}

bool UserList::updateUser(const string &username, const User &newUser)
{
    auto it = userList.find(username);
    if (it != userList.end())
    {
        User updatedUser = newUser;
        userList.erase(it);
        userList[updatedUser.getUserData().username] = updatedUser;
        return true;
    }
    return false;
}