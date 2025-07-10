#include "Signal.h"

void Signal::attach(Observer* observer)
{
    observers.push_back(observer);
}

void Signal::detach(Observer* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Signal::notify()
{
    for (auto& observer : observers)
    {
        observer->update();
    }
}