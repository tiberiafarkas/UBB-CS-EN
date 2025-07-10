#pragma once
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::istream;

class User {
private:
	string name;
	string type;
	int id;

public:
	User() {};
	User(string name, string type, int id) : name{name}, type{type}, id{id} {}
	~User() {};
	string getName() { return this->name; }
	string getType() { return this->type; }
	int getId() { return this->id;  }
	friend istream &operator >>(istream& is, User& u);
};
