#pragma once

#include <string>

class User
{
private:
	std::string name;
public:
	User();
	User(std::string name);
	std::string getName();
};