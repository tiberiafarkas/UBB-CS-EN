#pragma once

#include <vector>
#include "observer.h"

class Subject
{
private:
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void notify();
};