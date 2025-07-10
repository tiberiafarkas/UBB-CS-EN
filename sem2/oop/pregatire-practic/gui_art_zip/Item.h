#pragma once
#include <string>
#include <vector>

using namespace std;

class Item {

private:
    string name;
    string category;
    int price;
    vector<tuple<int, int, int>> list;

public:
    Item(string name, string category, int price, vector<tuple<int, int, int>> list);
    Item();

    string getName();
    string getCategory();
    int getPrice();
    vector<tuple<int, int, int>> getList();

    void setPrice(int newPrice);
    void setList(vector<tuple<int, int, int>> newList);


};
