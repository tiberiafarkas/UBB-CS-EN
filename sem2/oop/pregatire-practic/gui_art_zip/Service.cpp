//
// Created by teodo on 6/19/2024.
//

#include "Service.h"
#include <algorithm>

bool compare(Item a, Item b)
{
    return a.getPrice()<b.getPrice();
}

Service::Service() : repo(){

}

vector<Item> &Service::getItems() {
    vector<Item> &arr = repo.getItems();
    sort(arr.begin(), arr.end(), compare);
    return arr;
}

vector<User> &Service::getUsers() {
    return repo.getUsers();
}

void Service::readFromFileItems() {
    repo.readFromFileItems();

}

void Service::readFromFileUsers() {
    repo.readFromFileUsers();

}

void Service::saveToFileItems() {
    repo.saveToFileItems();

}

void Service::saveToFileUsers() {
    repo.saveToFileUsers();

}

vector<Item> Service::sortByCategory(string cateogory) {
    return repo.sortByCategory(cateogory);
}

void Service::addItem(Item item) {
    repo.addItem(item);
    notifyAllObservables();
    saveToFileUsers();
    saveToFileItems();

}

vector<tuple<int, int, int>> Service::getList(string name) {
    return repo.getList(name);
}

void Service::bid(string name, tuple<int, int, int> offer) {
    repo.bid(name, offer);
    saveToFileUsers();
    saveToFileItems();

}
