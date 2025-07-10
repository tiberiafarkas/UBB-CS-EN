#pragma once
#include <vector>

using std::vector;

class Observer {
public:
	Observer() = default;
	virtual void update() = 0;
	~Observer() = default;
};

class Subject {
public:
	vector<Observer*> observers;
	void addObserver(Observer* observer);
	void notify();
	~Subject() = default;
};