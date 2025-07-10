#include "observer.h"

void Subject::addObserver(Observer* observer) {
	observers.push_back(observer);
}

void Subject::notify() {
	for (auto observer : observers) {
		observer->update();
	}
}