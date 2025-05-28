#include "../../include/header.hpp"
using namespace std;

extern UserList *user_list;
extern GoodsList *goods_list;

void writeToFile() {
    
    ofstream user_file("../lib/user_list.txt");
    if (!user_file.is_open()) {
        cerr << "Error: Cannot open user_list.txt for writing\n";
        return;
    }

    try {
        auto user_list_map = user_list->getUserList();
        for (auto& user_pair : user_list_map) {
            User& user = user_pair.second;
            user_file << user.getUsername() << " "
                     << user.getPassword() << " "
                     << static_cast<int>(user.getRole()) << " "
                     << user.getIsDiscounted() << "\n";  
            
            
            const auto& discounts = user.getDiscountList();
            user_file << discounts.size() << "\n";
            for (const auto& discount : discounts) {
                user_file << discount.first << " " << discount.second << "\n";
            }

            
            auto& cart = user.getCart();
            const auto& cart_items = cart.getItems();
            user_file << cart_items.size() << "\n";
            for (const auto& item : cart_items) {
                if (item.goods) {
                    user_file << item.goods->getName() << " "
                             << item.quantity << " "
                             << static_cast<int>(item.status) << "\n";
                }
            }

            
            auto& order = user.getUserOrder();
            const auto& order_items = order.getItems();
            user_file << order_items.size() << "\n";
            for (const auto& item : order_items) {
                if (item.goods) {
                    user_file << item.goods->getName() << " "
                             << item.quantity << " "
                             << static_cast<int>(item.status) << "\n";
                }
            }
        }
    } catch (const exception& e) {
        cerr << "Error writing user data: " << e.what() << "\n";
    }
    user_file.close();

    
    ofstream goods_file("../lib/goods_list.txt");
    if (!goods_file.is_open()) {
        cerr << "Error: Cannot open goods_list.txt for writing\n";
        return;
    }

    try {
        for (const auto& goods_pair : goods_list->getGoodsList()) {
            const Goods& goods = goods_pair.second;
            goods_file << goods.getName() << " "
                      << goods.getDesc() << " "  
                      << static_cast<int>(goods.getCategory()) << " "  
                      << goods.getPrice() << " "
                      << goods.getStorage() << " "  
                      << goods.getIsDiscounted() << " "
                      << goods.getDiscountScale() << "\n";
        }
    } catch (const exception& e) {
        cerr << "Error writing goods data: " << e.what() << "\n";
    }
    goods_file.close();
}

void readFromFile() {
    
    ifstream user_file("../lib/user_list.txt");
    if (!user_file.is_open()) {
        cerr << "Warning: Cannot open user_list.txt for reading\n";
        return;
    }

    try {
        string username, password;
        int role;
        bool isDiscounted;
        
        while (user_file >> username >> password >> role >> isDiscounted) {
            
            int discount_count;
            user_file >> discount_count;
            
            unordered_map<int, int> discounts;
            for (int i = 0; i < discount_count; i++) {
                int threshold, amount;
                user_file >> threshold >> amount;
                discounts[threshold] = amount;
            }

            
            User user(username, password, static_cast<Role>(role), Cart(), Order(), isDiscounted, discounts);

            
            int cart_size;
            user_file >> cart_size;
            for (int i = 0; i < cart_size; i++) {
                string item_name;
                int quantity, status;
                user_file >> item_name >> quantity >> status;
                user.getCart().addItem(item_name, quantity);
            }

            
            int order_size;
            user_file >> order_size;
            for (int i = 0; i < order_size; i++) {
                string item_name;
                int quantity, status;
                user_file >> item_name >> quantity >> status;
                user.getUserOrder().addItem(item_name, quantity, static_cast<order_status>(status));
            }
            
            user_list->addUser(user);
        }
    } catch (const exception& e) {
        cerr << "Error reading user data: " << e.what() << "\n";
    }
    user_file.close();

    
    ifstream goods_file("../lib/goods_list.txt");
    if (!goods_file.is_open()) {
        cerr << "Warning: Cannot open goods_list.txt for reading\n";
        return;
    }

    try {
        string name, desc;
        int category;
        double price, discount_scale;
        int storage;
        bool is_discounted;
        
        while (goods_file >> name >> desc >> category >> price >> storage >> is_discounted >> discount_scale) {
            Goods goods(name, desc, static_cast<Category>(category), price, storage, is_discounted, discount_scale);
            goods_list->addGoods(goods);
        }
    } catch (const exception& e) {
        cerr << "Error reading goods data: " << e.what() << "\n";
    }
    goods_file.close();
}
