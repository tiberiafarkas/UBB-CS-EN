#ifndef CODE_REVISION_OBSERVER_H
#define CODE_REVISION_OBSERVER_H
#include <vector>
using namespace std;

class Observer {
public:
    virtual void update() = 0;

    virtual ~Observer();
};

class Subject {
private:
    vector<Observer*> arr;
public:
    void addObserver(Observer* o);
    void notify();
};


#endif //CODE_REVISION_OBSERVER_H
