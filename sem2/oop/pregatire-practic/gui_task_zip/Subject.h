
#pragma once
#include "Observer.h"
#include <vector>
#include <memory>

class Subject {
private:
    std::vector <std::unique_ptr<Observer> > observers;
public:
    Subject() = default;
    ~Subject() = default;
    void registerObserver(Observer *observer) { this->observers.emplace_back(observer); };
    void notify() { for (auto &observer : this->observers) observer->update(); };
};

