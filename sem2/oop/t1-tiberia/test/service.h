#pragma once
#include "Repository.h"

class Service {
private:
	Repository repo;
public:
	//function to add a subscription
	bool addSubscription(domain sub);

	//function to add entries in the repository
	void getEntries();

	//funciton to get all the subscriptions
	DynamicArray<domain> getSubscriptions();

	//function to get all the active subscriptions in the current month sorted by their company name
	DynamicArray<domain> getActiveSubscriptions(const string& date);
};
