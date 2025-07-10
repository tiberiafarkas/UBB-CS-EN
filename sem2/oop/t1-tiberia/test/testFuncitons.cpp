#include "test.h"
#include <assert.h>
#include <iostream>
#include <string>
#include "service.h"

void test::testAddSubscription() {
	this->service = Service();

	domain d1{ "Netflix", "15.04.2025", 12.99, true };
	domain d2{ "HBO", "16.03.2025", 10, true };
	domain d3{ "Amazon Prime", "18.04.2025", 15, true };

	this->service.addSubscription(d1);
	this->service.addSubscription(d2);
	this->service.addSubscription(d3);

	DynamicArray<domain> subs = this->service.getSubscriptions();

	assert(subs.getSize() == 3);
	assert(subs[0].getName() == "Netflix");
	assert(subs[1].getName() == "HBO");
	assert(subs[2].getName() == "Amazon Prime");

	assert(subs[0].getDate() == "15.04.2025");
	assert(subs[1].getDate() == "16.03.2025");
	assert(subs[2].getDate() == "18.04.2025");

	domain d4{ "Netflix", "15.04.2025", 12.99, false };
	assert(this->service.addSubscription(d4) == false);
	assert(subs.getSize() == 3);
}

void test::testGetActiveSubscriptionsSorted() {
	this->service = Service();

	domain d1{ "Netflix", "15.04.2025", 12.99, 0 };
	domain d2{ "HBO", "16.03.2025", 10, 1 };
	domain d3{ "Amazon Prime", "18.04.2025", 15, 1 };
	domain d4{ "Disney+", "20.04.2025", 5.78, 1 };
	domain d5{ "Hulu", "21.03.2025", 9, 0 };
	domain d6{ "Apple TV", "06.02.2025", 8.65, 0 };

	this->service.addSubscription(d1);
	this->service.addSubscription(d2);
	this->service.addSubscription(d3);
	this->service.addSubscription(d4);
	this->service.addSubscription(d5);
	this->service.addSubscription(d6);

	DynamicArray<domain> subs = this->service.getActiveSubscriptions("01.04.2025");
	assert(subs.getSize() == 2);
	assert(subs[0].getName() == "Amazon Prime");
	assert(subs[1].getName() == "Disney+");
}

void test::testAll() {
	this->testAddSubscription();
	this->testGetActiveSubscriptionsSorted();
	std::cout << "All tests passed!\n";
}