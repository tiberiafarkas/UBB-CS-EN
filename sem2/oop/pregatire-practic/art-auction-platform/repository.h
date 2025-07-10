#pragma once
#include "user.h"
#include "item.h"

class Repository {
private:
	vector<User> users;
	vector<Item> items;

public:
	Repository() {
		this->load();
	}
	~Repository() {};
	void load();
	void saveFile();
	vector<User> getUsers() { return users; };
	vector<Item> getItems() { return items; };
	void addItem(Item item);
	void addOffer(tuple<int, string, int> offer, Item it) {
		it.addOffer(offer);
	}
	void updatePrice(Item it, int newPrice) {
		it.setPrice(newPrice);
	}
	vector<tuple<int, string, int>> getOffers(Item it) {
		return it.getOffersList();
	}
};