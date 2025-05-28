#include "../../include/header.hpp"

extern UserList *user_list;
extern GoodsList *goods_list;

namespace {
    fstream file;
}

void writeToFile() {
    file.open(ROOT_DIR + "lib/" + USER_FILE, ios::out);
    for (auto &user : user_list->getUserList()) {
        file << user.first << " " << user.second.getPassword() << " " << user.second.getRole() << endl;
        if (user.second.getCart().getSize() > 0) {
            file << "cart" << endl;
            for (auto &item : user.second.getCart().getItems()) {
                file << item.goods->getName() << " " << item.quantity << " " << item.status << endl;
            }
            file << "cart end" << endl;
        }
        if (user.second.getUserOrder().getItems().size() > 0) {
            file << "order" << endl;
            for (auto &item : user.second.getUserOrder().getItems()) {
                file << item.goods->getName() << " " << item.quantity << " " << item.status << endl;
            }
            file << "order end" << endl;
        }
        if (user.second.getIsDiscounted()) {
            file << "discount" << endl;
            for (auto &item : user.second.getDiscountList()) {
                file << item.first << " " << item.second << endl;
            }
            file << "discount end" << endl;
        }
        file << endl;
    }
    file.close();

    file.open(ROOT_DIR + "lib/" + GOODS_FILE, ios::out);
    for (auto &goods : goods_list->getGoodsList()) {
        file << goods.first << " " << goods.second.getDesc() << " " << goods.second.getCategory() << " " << goods.second.getPrice() << " " << goods.second.getStorage() << endl;
        if (goods.second.getIsDiscounted()) {
            file << "discount" << endl;
            file << goods.second.getDiscountScale() << endl;
            file << "discount end" << endl;
        }
    }
    file.close();
}

void readFromFile() {
    file.open(ROOT_DIR + "lib/" + USER_FILE, ios::in);
    if (!file.is_open()) {
        cout << "Failed to open user file" << endl;
        return;
    }
    string line;
    User user;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password, role;
        ss >> username >> password >> role;
        user.setUsername(username);
        user.setPassword(password); 
        user.setRole(role);
        user.setIsDiscounted(true);
        if (line == "cart") {
            Cart cart;
            stringstream ss(line);
            while (getline(file, line)) {
                if (line == "cart end") {
                    break;
                }
                string name, quantity, status;
                ss >> name >> quantity >> status;
                Goods *goods = goods_list->findGoodsByName(name).back();
                if (goods) {
                    string name = goods->getName();
                    cart.addItem(name, stoi(quantity));
                    cart.getItem(name).status = order_status(stoi(status));
                }
            }
        }
        if (line == "order") {
            Order order;
            stringstream ss(line);
            while (getline(file, line)) {
                if (line == "order end") {
                    break;
                }
                string name, quantity, status;
                ss >> name >> quantity >> status;
                Goods *goods = goods_list->findGoodsByName(name).back();
                if (goods) {
                    string name = goods->getName();
                    order.addItem(name, stoi(quantity), order_status(stoi(status)));
                } 
            }
            user.setUserOrder(order);
        }
        if (line == "discount") {
            unordered_map<int, int> discountList;
            stringstream ss(line);
            while (getline(file, line)) {
                if (line == "discount end") {
                    break;
                }
                int discount, limit;
                ss >> discount >> limit;
                discountList[discount] = limit;
            }
            user.setDiscountList(discountList);
        }
    }
    file.close();

    file.open(ROOT_DIR + "lib/" + GOODS_FILE, ios::in);
    if (!file.is_open()) {
        cout << "Failed to open goods file" << endl;
        return;
    }
    Goods goods;
    stringstream ss(line);
    while (getline(file, line)) {
        stringstream ss(line);
        string name, desc, category, price, storage;
        ss >> name >> desc >> category >> price >> storage;
        goods.setName(name);
        goods.setDesc(desc);
        goods.setCategory(category);
        goods.setPrice(stod(price));
        goods.setStorage(stoi(storage));
        if (line == "discount") {
            goods.setIsDiscounted(true);
            double discountScale;
            ss >> discountScale;
            goods.setDiscountScale(discountScale);
        }
        goods_list->addGoods(goods);
    }
    file.close();
}