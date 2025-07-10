#include <iostream>

using namespace std;

class B {
public:
    void f() {
        cout << "B.f ";
    }
    virtual ~B() {}
};

class D1 : public B {
public: 
    virtual void f() {
        cout << "D1.f ";
    }
    virtual ~D1() {}
};

class D2 : public D1 {
public:
    void f() {
        cout << "D2.f ";
    }
};

int main()
{
    B* b1 = new B{}; //an object of type B with pointer to B
    b1->f(); // B.f
    delete b1;
    B* b2 = new D1{}; //an object of type D1 with pointer to B 
    b2->f(); //the function is NOT virtual so it calls the B's f() method => B.f
    delete b2;
    B* b3 = new D2{}; //an object of type D2 with pointer to B
    b3->f(); //the function is NOT virtual so it calls B's method => B.f
    delete b3;
    D1* d = new D2{}; //an object of type D2 with pointer to D1
    d->f(); // D2.f
    delete d;

    //output:
    //B.f B.f B.f D2.f

    //if the function f had been virtual, the output ould have been \
    // B.f D1.f D2.f D2.f

    //once the base class define a function virtual, all the classes which inherit that class\
    have that function virtual even if it is declared virtual or not
}
