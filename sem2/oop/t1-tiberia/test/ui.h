#pragma once
#include "DynamicArray.h"
#include "domain.h"
#include "service.h"

class UI {
private:
	Service service;
public:
	void printMenu();
	void addSubscription();
	void showSubscriptions();
	void showActiveSubscriptions();
	void run();
};
