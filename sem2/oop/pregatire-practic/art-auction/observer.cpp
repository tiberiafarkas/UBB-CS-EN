#include "observer.h"

void Subject::notifyAllObservers() {
	for (auto& observer : observers) {
		observer->update();
	}
}

void Subject::addObserver(Observer* observer) {
	observers.push_back(observer);
}