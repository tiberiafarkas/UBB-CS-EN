#pragma once
#include <string>

using std::string;

class Building {
protected:
	string address;
	int constructionYear;

public:
	Building(string address, int constructionYear);
	virtual ~Building() {}; // virtual destructor
	virtual bool mustBeRestored() = 0; // pure virtual function
	virtual bool canBeDemolished() = 0; // pure virtual function
	virtual string toString();
	string getAddress() const { return address; } // added getter for address
	int getConstructionYear() const { return constructionYear; } // added getter for construction year
};

class Block : public Building {
private:
	int totalApartaments;
	int occupiedApartaments;

public:
	Block(string address, int constructionYear, int totalApartaments, int occupiedApartaments);
	~Block() override {};
	bool mustBeRestored();
	bool canBeDemolished();
	string toString();
};

class House : public Building {
private:
	string type;
	bool isHistorical;

public:
	House(string address, int constructionYear, string type, bool isHistorical);
	~House() override {};
	bool mustBeRestored();
	bool canBeDemolished();
	string toString();
};