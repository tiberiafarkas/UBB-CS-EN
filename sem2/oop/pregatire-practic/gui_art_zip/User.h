#pragma once

#include <string>

using namespace std;

class User {

private:
    string name;
    int id;
    string type;

public:
    User(string name, int id, string type);
    User();

    string getName();
    int getId();
    string getType();
};

