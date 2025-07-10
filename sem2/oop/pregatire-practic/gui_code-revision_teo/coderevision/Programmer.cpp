//
// Created by Dragos on 6/30/2022.
//

#include "Programmer.h"

Programmer::Programmer(const string &name, int revised, int mustRevise) : name(name), revised(revised),
                                                                          must_revise(mustRevise) {}

Programmer::Programmer() {
    name = "";
    revised = 0;
    must_revise = 0;
}

Programmer::~Programmer() {

}

const string &Programmer::getName() const {
    return name;
}

void Programmer::setName(const string &name) {
    Programmer::name = name;
}

int Programmer::getRevised() const {
    return revised;
}

void Programmer::setRevised(int revised) {
    Programmer::revised = revised;
}

int Programmer::getMustRevise() const {
    return must_revise;
}

void Programmer::setMustRevise(int mustRevise) {
    must_revise = mustRevise;
}

ostream &operator<<(ostream &os, const Programmer &programmer) {
    os << programmer.name << "," << programmer.revised << "," << programmer.must_revise;
    return os;
}

vector<string> tokenize2(string str, char delimiter)
{
    vector <string> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

istream &operator>>(istream &is, Programmer &p){
    string line;
    getline(is, line);

    vector<string> tokens = tokenize2(line, ',');
    if (tokens.size() != 3)
        return is;
    p.setName(tokens[0]);
    p.setRevised(std::stoi(tokens[1]));
    p.setMustRevise(std::stoi(tokens[2]));
    return is;
}