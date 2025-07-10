#pragma once

#include "Repository.h"
#include "Observer.h"

class Service : public Subject {

private:
    Repository repo;

public:
    Service();

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

};
