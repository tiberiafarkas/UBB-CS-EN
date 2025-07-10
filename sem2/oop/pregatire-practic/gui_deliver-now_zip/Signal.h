#pragma once
#include <vector>
#include <algorithm>
#include "Observer.h"
class Signal {
public:
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify();
private:
    std::vector<Observer*> observers;
};