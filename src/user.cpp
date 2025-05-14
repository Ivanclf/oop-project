#include "../include/header.hpp"
using namespace std;

User::User() : username(""), password(""), role(customer)  {}
User::User(string name, string pwd, Role r) : username(name), password(pwd), role(r) {}

string User::getUsername() const { return username; }

void User::setUsername(const string &name) { username = name; }

string User::getPassword() const { return password; }

void User::setPassword(const string &pwd) { password = pwd; }

Role User::getRole() const { return role; }

void User::setRole(Role r) { role = r; }

Cart &User::getCart() { return userCart; }

unordered_map<string, User> UserList::getUserList() const { return userList; }

vector<User> UserList::findUserByUsername(const string &username) const
{
    vector<User> result;
    auto it = userList.find(username);
    if (it != userList.end())
        result.push_back(it->second);
    return result;
}

void UserList::iterateUsers() const
{
    for (const auto &pair : userList)
        cout << "Username: " << pair.first << ", Role: " << (pair.second.getRole() == admin ? "Admin" : "Customer") << endl;
}

vector<User> UserList::findUsersByRole(Role role) const
{
    vector<User> result;
    for (const auto &pair : userList)
    {
        if (pair.second.getRole() == role)
        {
            result.push_back(pair.second);
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
        userList[updatedUser.getUsername()] = updatedUser;
        return true;
    }
    return false;
}
