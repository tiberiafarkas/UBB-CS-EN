#pragma once
#include "repository.h"
#include "observer.h"
#define offerFormat vector<tuple<int, string, int>>


class Service : public Subject {
private:
	Repository repo;

public:
	vector<User> getUsers() { return repo.getUsers(); }
	vector<Item> getItems() { return repo.getItems(); }
	vector<Item> getItemsByCategory(string category);
	void addItem(string name, string category, int price, vector<tuple<int, string, int>> offer);
	offerFormat getOffers(Item it);
	void bid(Item it, int id, string date, int newPrice);
};