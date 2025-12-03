#pragma once
#include <vector>

class Observer {
public:
	Observer() = default;
	virtual void update() = 0;
	~Observer() = default;
};

class Subject {
protected:
	std::vector<Observer*> observers;

public:
	Subject() = default;
	void notifyAllObservers();
	void addObserver(Observer* observer);
	~Subject() = default;
};