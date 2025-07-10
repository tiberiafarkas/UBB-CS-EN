#pragma once

#include <string>

class Writer
{
private:
	std::string name;
	std::string expertise;
public:
	Writer(); 
	Writer(std::string name, std::string expertise);
	std::string getName();
	std::string getExpertise();
};