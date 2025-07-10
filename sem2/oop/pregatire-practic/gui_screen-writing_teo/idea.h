#pragma once

#include <string>

class Idea
{
private:
	std::string description;
	std::string status;
	std::string creator;
	int act;
public:
	Idea();
	Idea(std::string description, std::string status, std::string creator, int act);
	std::string getDescription();
	std::string getStatus();
	std::string getCreator();
	int getAct();
	void setStatus(std::string newStatus);
};