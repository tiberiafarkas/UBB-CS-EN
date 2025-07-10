#pragma once

#include <vector>
#include "Item.h"
#include "User.h"

using namespace std;

class Repository {

private:
    vector<Item> arrItem;
    vector<User> arrUser;

public:

    Repository();

    vector<Item> &getItems();
    vector<User> &getUsers();

    void readFromFileItems();
    void readFromFileUsers();

    void saveToFileItems();
    void saveToFileUsers();

    vector<Item> sortByCategory(string cateogory);
    void addItem(Item item);
    vector<tuple<int, int, int>> getList(string name);
    void bid(string name, tuple<int, int, int> offer);

    vector<string> split(string line, char delim);

};


