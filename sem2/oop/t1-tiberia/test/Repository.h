#pragma once
#include "DynamicArray.h"
#include "domain.h"

class Repository {
private:
	DynamicArray<domain> subscriptions;
public:
	//constructor
	Repository();
	//destructor
	~Repository();

	//add a subscription
	bool addSubscription(domain s);
	DynamicArray<domain> getSubscriptions();
};
