#include "../../include/header.hpp"
extern UserList *user_list;
extern GoodsList *goods_list;

namespace {
    bool isValidNumber(const string& str) {
        if (str.empty()) return false;
        bool hasDecimal = false;
        bool hasDigit = false;
        for (size_t i = 0; i < str.size(); ++i) {
            if (isdigit(str[i])) {
                hasDigit = true;
            } else if (str[i] == '.') {
                if (hasDecimal) return false;
                hasDecimal = true;
            } else if (str[i] != '-' && str[i] != '+') {
                return false;
            }
        }
        return hasDigit;
    }
    
    void replaceAllUnderscoreWithSpace(string& str) {
        for (size_t i = 0; i < str.size(); ++i) {
            if (str[i] == '_') {
                str.replace(i, 1, " ");
            }
        }
    }
}

void writeToFile() {
    ofstream userFile(ROOT_DIR + "lib/" + USER_FILE, ios::out);
    ofstream goodsFile(ROOT_DIR + "lib/" + GOODS_FILE, ios::out);
    
    for (auto &user : user_list->getUserList()) {
        userFile << user.first << " " << user.second.getPassword() << " " << user.second.getRole() << endl;
        if (user.second.getCart().getSize() > 0) {
            userFile << "cart" << endl;
            for (auto &item : user.second.getCart().getItems()) {
                userFile << item.goods->getName() << " " << item.quantity << " " << item.status << endl;
            }
            userFile << "cart end" << endl;
        }
        if (user.second.getUserOrder().getItems().size() > 0) {
            userFile << "order" << endl;
            for (auto &item : user.second.getUserOrder().getItems()) {
                userFile << item.goods->getName() << " " << item.quantity << " " << item.status << endl;
            }
            userFile << "order end" << endl;
        }
        if (user.second.getIsDiscounted() && user.second.getDiscountList().size() > 0) {
            userFile << "discount" << endl;
            for (auto &item : user.second.getDiscountList()) {
                userFile << item.first << " " << item.second << endl;
            }
            userFile << "discount end" << endl;
        }
        userFile << endl;
    }
    userFile.close();

    for (auto &goods : goods_list->getGoodsList()) {
        goodsFile << goods.first << " " << goods.second.getDesc() << " " << goods.second.getCategory() << " " << goods.second.getPrice() << " " << goods.second.getStorage() << endl;
        if (goods.second.getIsDiscounted() && goods.second.getDiscountScale() != 1.0) {
            goodsFile << "discount" << endl;
            goodsFile << goods.second.getDiscountScale() << endl;
            goodsFile << "discount end" << endl;
        }
    }
    goodsFile.close();
}

void readFromFile() {
    string line;
    
    ifstream goodsFile(ROOT_DIR + "lib/" + GOODS_FILE, ios::in);
    if (!goodsFile.is_open()) {
        cout << "Failed to open goods file" << endl;
        return;
    }
    while (getline(goodsFile, line)) {
        Goods goods;
        stringstream goodsIss(line);
        string name, desc, category, price, storage;
        if(goodsIss >> name >> desc >> category >> price >> storage) {
            replaceAllUnderscoreWithSpace(name);
            replaceAllUnderscoreWithSpace(desc);
            if(goods_list->findGoodsByName(name).size() > 0)
                continue;
            if (!isValidNumber(price) || !isValidNumber(storage)) {
                cout << "Invalid price or storage" << endl;
                goods.setPrice(0.0);
                goods.setStorage(0);
            } else {
                goods.setPrice(stod(price));
                goods.setStorage(stoi(storage));
            }
            goods.setDesc(desc);
            goods.setCategory(category);
            goods.setName(name);
            goods_list->addGoods(goods);
        }

        if(getline(goodsFile, line) && line == "discount") {
            goods.setIsDiscounted(true);

            if(getline(goodsFile, line)) {
                if(!line.empty() && isValidNumber(line)) {
                    goods.setDiscountScale(stod(line));
                } else {
                    cout << "Invalid discount scale" << endl;
                    goods.setDiscountScale(1.0);
                }
            }

            if(getline(goodsFile, line) && line != "discount end") {
                cout << "Invalid discount end line" << endl;
            }
        }
        goods_list->addGoods(goods);
    }
    goodsFile.close();

    ifstream userFile(ROOT_DIR + "lib/" + USER_FILE, ios::in);
    if (!userFile.is_open()) {
        cout << "Failed to open user file" << endl;
        return;
    }
    while (getline(userFile, line)) {
        User user;
        stringstream userIss(line);
        string username, password, role;
        if (userIss >> username >> password >> role) {
            user.setUsername(username);
            user.setPassword(password);
            user.setRole(role);
        }
        while (getline(userFile, line)) {
            if (line.empty() || (line.find(' ') != string::npos && line != "discount end")) {
                userFile.seekg(-static_cast<int>(line.size()) - 1, ios_base::cur);
                break;
            }
            
            if (line == "cart") {
                Cart cart;
                while (getline(userFile, line) && line != "cart end") {
                    istringstream cartIss(line);
                    string name, quantity, status;
                    if(cartIss >> name >> quantity >> status) {
                        auto goods = goods_list->findGoodsByName(name);
                        if (!goods.empty()) {
                            cart.addItem(name, stoi(quantity));
                            cart.getItem(name).status = order_status(stoi(status));
                        }
                    }
                }
                user.setCart(cart);
            }
            else if (line == "order") {
                Order order;
                while (getline(userFile, line) && line != "order end") {
                    istringstream orderIss(line);
                    string name, quantity, status;
                    if(orderIss >> name >> quantity >> status) {
                        auto goods = goods_list->findGoodsByName(name);
                        if (!goods.empty()) {
                            order.addItem(name, stoi(quantity), order_status(stoi(status)));
                        }
                    } 
                }
                user.setUserOrder(order);
            }
            else if (line == "discount") {
                unordered_map<int, int> discountList;
                while (getline(userFile, line) && line != "discount end") {
                    istringstream discountIss(line);
                    int limit, discount;
                    if(discountIss >> limit >> discount) {
                        discountList[limit] = discount;
                    }
                }
                user.setDiscountList(discountList);
            }
        }
        user_list->addUser(user);
    }
    userFile.close();

    user_list->iterateUsers();
}