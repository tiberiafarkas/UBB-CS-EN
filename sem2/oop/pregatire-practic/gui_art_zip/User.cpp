//
// Created by teodo on 6/19/2024.
//

#include "User.h"

User::User(string name, int id, string type) {
    this->name = name;
    this->id = id;
    this->type = type;

}

string User::getName() {
    return this->name;
}

int User::getId() {
    return this->id;
}

string User::getType() {
    return this->type;
}

User::User() = default;
