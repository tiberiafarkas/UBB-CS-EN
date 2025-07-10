#pragma once
#include <QWidget>
#include "service.h"

class Observer {
public:
	Observer() = default;
	virtual void update() = 0;
	~Observer() = default;
};

class Subject {
protected:
	vector<Observer*> observers;

public:
	Subject() = default;
	void notifyAllObservers();
	void addObserver(Observer* observer);
	~Subject() = default;
};