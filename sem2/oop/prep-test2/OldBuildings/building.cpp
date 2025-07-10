#include "building.h"
#include <iostream>

Building::Building(string address, int constructionYear) : address(address), constructionYear(constructionYear) {}

string Building::toString() {
	return "Address: " + address + "\nConstruction Year: " + std::to_string(constructionYear) + '\n';
}

Block::Block(string address, int constructionYear, int totalApartaments, int occupiedApartaments)
	: Building(address, constructionYear), totalApartaments(totalApartaments), occupiedApartaments(occupiedApartaments) {
}

bool Block::mustBeRestored() {
	double occupancyRate = (double)(occupiedApartaments) / (double)(totalApartaments);
	if (constructionYear < 1985 && occupancyRate > 0.8) {
		return true;
	}
	return false;
}

bool Block::canBeDemolished() {
	double occupancyRate = (double)(occupiedApartaments) / (double)(totalApartaments);	
	if (occupancyRate < 0.05) {
		return true;
	}
	return false;
}

string Block::toString() {
	return "Block: " + address + "\nConstruction Year: " + std::to_string(constructionYear) + "\nTotal Apartaments: " + std::to_string(totalApartaments) + "\nOccupied Apartaments " + std::to_string(occupiedApartaments) + '\n';
}

House::House(string address, int constructionYear, string type, bool isHistorical)
	: Building(address, constructionYear), type(type), isHistorical(isHistorical) {
}

bool House::mustBeRestored() {
	if (constructionYear < 1925) {
		return true;
	}
	return false;
}

bool House::canBeDemolished() {
	if (isHistorical) {
		return false;
	}
	return true;
}

string House::toString() {
	return "House: " + address + "\nConstruction Year: " + std::to_string(constructionYear) + "\nType: " + type + "\nIs Historical: " + (isHistorical ? "Yes" : "No") + '\n';
}