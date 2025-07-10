#pragma once
#include "oberserver.h"
#include <vector>

using std::vector;

class Subject {
private:
	vector<Obersver*> observers;
public:
	void registerObserver(Obersver* observer) {
		observers.push_back(observer);
	}

	void unregisterObserver(Obersver* observer) {
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}

	void notifyObservers() {
		for (Obersver* observer : observers) {
			observer->update();
		}
	}

};