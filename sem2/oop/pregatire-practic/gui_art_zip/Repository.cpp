//
// Created by teodo on 6/19/2024.
//

#include <fstream>
#include <sstream>
#include "Repository.h"

Repository::Repository() : arrItem(0), arrUser(0){

}

vector<Item> &Repository::getItems() {
    return arrItem;
}

vector<User> &Repository::getUsers() {
    return arrUser;
}

void Repository::readFromFileItems() {
    ifstream file("items.txt");
    if(!file.is_open())
        throw exception();

    string line;
    while(getline(file, line))
    {
        vector <string> items;
        items = split(line, ',');
        vector<tuple<int, int, int> > list;
        for(int i=3;i<items.size();i=i+3)
            list.push_back(make_tuple(stoi(items[i]),stoi(items[i+1]),stoi(items[i+2])));

        Item item = Item(items[0],items[1],stoi(items[2]), list);
        arrItem.push_back(item);

    }
    file.close();
}

void Repository::readFromFileUsers() {
    ifstream file("users.txt");
    if(!file.is_open())
        throw exception();

    string line;
    while(getline(file, line))
    {
        vector <string> items;
        items = split(line, ',');
        User user = User(items[0], stoi(items[1]), items[2]);
        arrUser.push_back(user);

    }
    file.close();

}

vector<string> Repository::split(string line, char delim) {
    vector<string> tokens;
    stringstream ss{line};
    string current;
    while (getline(ss, current, delim))
    {
        tokens.push_back(current);
    }
    return tokens;
}

void Repository::saveToFileItems() {
    ofstream g("items.txt");
    for(auto i:arrItem)
    {
        g<<i.getName()<<","<<i.getCategory()<<","<<i.getPrice()<<",";
        for(auto j:i.getList())
            g<<get<0>(j)<<","<<get<1>(j)<<","<<get<2>(j)<<",";
        g<<'\n';
    }
    g.close();

}

void Repository::saveToFileUsers() {
    ofstream g("users.txt");
    for(auto i:arrUser) {
        g << i.getName() << "," << i.getId() << "," << i.getType()<<'\n';
    }
    g.close();

}

vector<Item> Repository::sortByCategory(string category) {
    vector<Item> arr;
    for(auto i:arrItem)
    {
        if(i.getCategory() == category)
            arr.push_back(i);
    }
    return arr;
}

void Repository::addItem(Item item) {
    arrItem.push_back(item);

}

vector<tuple<int, int, int>> Repository::getList(string name) {
    for(auto i:arrItem)
        if(i.getName() == name)
            return i.getList();
}

void Repository::bid(string name, tuple<int, int, int> offer) {
    for(auto i:arrItem)
    {
        if(i.getName() == name) {
            i.setPrice(get<2>(offer));
            vector<tuple<int, int, int>> list = i.getList();
            list.push_back(offer);
            i.setList(list);
        }

    }

}
