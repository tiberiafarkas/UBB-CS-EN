#pragma once
#include "service.h"

class test {
private:
	Service service;
	void testAddSubscription();
	void testGetActiveSubscriptionsSorted();
public:
	void testAll();
};