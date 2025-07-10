#include "service.h"
#include <iostream>
/*
	Adds a subscription to the repository
	Input: s - domain
	Output: true - if the subscription was added successfully
			false - if the subscription already exists
*/
bool Service::addSubscription(domain s) {
	return this->repo.addSubscription(s);
}

void Service::getEntries() {
	domain d1{ "Netflix", "15.04.2025", 12.99, false };
	domain d2{ "HBO", "16.03.2025", 10, true };
	domain d3{ "Amazon Prime", "18.04.2025", 15, true };
	domain d4{ "Disney+", "20.04.2025", 5.78, true };
	domain d5{ "Hulu", "21.03.2025", 9, false };
	domain d6{ "Apple TV", "06.02.2025", 8.65, true };
	this->repo.addSubscription(d1);
	this->repo.addSubscription(d2);
	this->repo.addSubscription(d3);
	this->repo.addSubscription(d4);
	this->repo.addSubscription(d5);
	this->repo.addSubscription(d6);

}

DynamicArray<domain> Service::getSubscriptions() {
	return this->repo.getSubscriptions();
}

/*
	Returns all the active subscriptions given the current month sorted by name and total value
	It searches for the active subscriptions in the repository and if they are active and the month is the current one, it adds them to a new dynamic array
	Then it sorts the new dynamic array by name
	Input: date - string
	Output: sorted_subscriptions - DynamicArray<domain>
*/ 

DynamicArray<domain> Service::getActiveSubscriptions(const string& date) {
	DynamicArray<domain> sorted_subscriptions;
	DynamicArray<domain> subscriptions = this->repo.getSubscriptions();

	for (int i = 0; i < subscriptions.getSize(); i++) {
		if (subscriptions[i].isActive() == true && subscriptions[i].getDate().substr(3, 2) == date.substr(3, 2)) {
			sorted_subscriptions.add(subscriptions[i]);
		}
	}

	for (int i = 0; i < sorted_subscriptions.getSize() - 1; i++) {
		for (int j = i + 1; j < sorted_subscriptions.getSize(); j++) {
			if (sorted_subscriptions[i].getName() > sorted_subscriptions[j].getName() ) {
				domain aux = sorted_subscriptions[i];
				sorted_subscriptions[i] = sorted_subscriptions[j];
				sorted_subscriptions[j] = aux;
			}
		}
	}

	return sorted_subscriptions;
}
