
#pragma once
#include <iostream>

class Person {
private:
    std::string name, role;
public:
    Person(std::string name = "", std::string role = "") : name{name}, role{role} {};
    std::string getName() const
    {
        return this->name;
    }
    std::string getRole() const
    {
        return this->role;
    }
};

