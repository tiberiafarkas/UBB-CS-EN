#include "user.h"

User::User()
{
	name = "";
}

User::User(std::string name)
{
	this->name = name;
}

std::string User::getName()
{
	return name;
}
