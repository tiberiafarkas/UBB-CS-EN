//
// Created by teodo on 6/19/2024.
//

#include "Item.h"

Item::Item(string name, string category, int price, vector<tuple<int, int, int>> list) {
    this->name = name;
    this->category = category;
    this->price = price;
    this->list = list;

}

string Item::getName() {
    return this->name;
}

string Item::getCategory() {
    return this->category;
}

int Item::getPrice() {
    return this->price;
}

vector<tuple<int, int, int>> Item::getList() {
    return this->list;
}

void Item::setPrice(int newPrice) {
    this->price = newPrice;

}

void Item::setList(vector<tuple<int, int, int>> newList) {
    this->list = newList;

}

Item::Item() = default;
