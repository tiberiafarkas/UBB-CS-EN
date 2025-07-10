#pragma once
#include <string>

using std::string;

class User {
private:
	string username;
	string name;

public:
	User(const string& username, const string& name): username(username), name(name) {}
	string getUser() const {
		return username;
	}
};
