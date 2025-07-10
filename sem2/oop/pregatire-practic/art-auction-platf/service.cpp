#include "service.h"
#include <algorithm>

using std::sort;

vector<Item> Service::getItemsByCategory(string category) {
	vector<Item> items = repo.getItems();
	vector<Item> itemsByCategory;

	for (auto i : items) {
		if (i.getCategory() == category) {
			itemsByCategory.push_back(i);
		}
	}

	return itemsByCategory;
}

void Service::addItem(string name, string category, int price, vector<tuple<int, string, int>> offer) {
	if (name == "")
		throw std::exception("Empty name");
	if (price <= 0)
		throw std::exception("Invalid price");

	Item it{ name, category, price, offer };
	repo.addItem(it);
}

offerFormat Service::getOffers(Item it) {
	offerFormat offers = it.getOffersList();
	sort(offers.begin(), offers.end(), [](tuple<int,string,int> &a, tuple<int,string,int> &b) {
		return std::get<1>(a) > std::get<1>(b);
		});

	return offers;
}

void Service::bid(Item it, int id, string date, int newPrice) {
	if (newPrice < it.getPrice())
		throw std::exception("Sum offered smaller than the current price of the item!");

	repo.updatePrice(it, newPrice);
	tuple<int, string, int> offer{ id, date, newPrice };
	repo.addOffer(offer, it);
}