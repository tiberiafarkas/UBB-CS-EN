#include <iostream>
using namespace std;

class A {
public:
    A() {}
    A(const A& other) { cout << "copyA "; }
    virtual void show() { cout << "A.show "; }
    void process(A a) { cout << "A.process "; }
    virtual ~A() { cout << "~A "; }
};

class C : public A {
public:
    C() {}
    void show() override { A::show(); cout << "C.show "; }
    void process(C c) { A::process(c); cout << "C.process "; }
    ~C() override { cout << "~C "; }
};

int main() {
    A* a1 = new A{}; //creates an A object, the constructor is empty => no printing
    A* a2 = new C{}; //creates a C object, but the pointer is of type A, both constructors are empty => no printing
    a2->show(); //show() is virtual so it calls C's show() method, which calls A's show() method => output: A.show C.show
    a2->process(*a1); //process() is not virtual so it calls A's process() method and *a1 is passed by value not by reference, so the copy construct is called => copyA A.process, then \
    the destructor of A is called as we have done a copy => ~A
    delete a1; //calls the destructor of A => ~A
    delete a2; //the destructor is virtual, so calls the destructor of C => ~C, but the base class is also called => ~A \
    this happens because the destructor of A's is virtual and the object was created as a C 

    //output:
    //A.show C.show copyA A.process ~A ~A ~C ~A
    return 0;
}
