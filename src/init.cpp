#include "../include/header.hpp"
using namespace std;
extern UserList *user_list;
extern GoodsList *goods_list;

void __init__()
{
    
    ifstream user_file_check("../lib/user_list.txt");
    ifstream goods_file_check("../lib/goods_list.txt");
    
    if (user_file_check.is_open() && goods_file_check.is_open()) {
        user_file_check.close();
        goods_file_check.close();
        readFromFile();
        return;
    }
    
    ofstream user_file("../lib/user_list.txt");
    if (user_file.is_open()) {
        unordered_map<int, int> empty_map;
        unordered_map<int, int> d_map = {{100, 10}, {200, 15}, {300, 20}};
        
        
        user_file << "admin 123456 0 0 " 
                 << "0\n"; 
        
        
        user_file << "xiaoming 123456 1 0 "
                 << "0\n";
                 
        
        user_file << "haohao 88888888 1 0 "
                 << "0\n";
                 
        
        user_file << "d 2 1 1 " 
                 << "3 " 
                 << "100 10 200 15 300 20\n"; 
                 
        user_file.close();
    }

    ofstream goods_file("../lib/goods_list.txt");
    if (goods_file.is_open()) {
        goods_file << "eggs the_cheapest! 0 9.99 50 1 0.9\n"
                  << "shampoo keep_your_hair_clean! 2 25 200 1 0.5\n"
                  << "jacket same_as_Huang_renxun 1 362.8 5 1 0.7\n"
                  << "toddlering_vehicle absolutely_safe! 3 400 5 1 0.8\n"
                  << "eggplant fresh_now 0 5.68 100 1 0.9\n"
                  << "apple import_from_China 0 10.58 300 1 0.9\n";
        goods_file.close();
    }
    
    
    readFromFile();
}