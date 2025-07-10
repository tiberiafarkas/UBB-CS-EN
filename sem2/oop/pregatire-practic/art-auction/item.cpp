#include "item.h"
#include <sstream>

using std::stringstream;

istream& operator>>(istream& is, Item& item) {
	string line;
	if (getline(is, line)) {
		stringstream ss(line);
		getline(ss, item.name, '|');
		getline(ss, item.category, '|');
		ss >> item.price;
		string offer;
		while (getline(ss, offer, '|')) {
			stringstream offerStream(offer);
			int id;
			string name;
			int price;
			offerStream >> id;
			getline(offerStream, name, ',');
			offerStream >> price;
			item.offersList.emplace_back(id, name, price);
		}
	}
	return is;
}

ostream& operator<<(ostream& os, Item item) {
	os << item.name << '|' << item.category << '|' << item.price;
	for (const auto& offer : item.offersList) {
		os << '|' << std::get<0>(offer) << ',' << std::get<1>(offer) << ',' << std::get<2>(offer);
	}
	return os;
}

