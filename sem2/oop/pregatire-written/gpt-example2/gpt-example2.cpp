#include <iostream>
using namespace std;

class X {
public:
    X() {}
    X(const X&) { cout << "copyX "; }
    virtual void act() { cout << "X.act "; }
    void use(X x) { cout << "X.use "; }
    virtual ~X() { cout << "~X "; }
};

class Y : public X {
public:
    Y() {}
    Y(const Y&) { cout << "copyY "; }
    void act() override { cout << "Y.act "; }
    void use(Y y) { cout << "Y.use "; }
    virtual ~Y() { cout << "~Y "; }
};

class Z : public Y {
public:
    Z() {}
    Z(const Z&) { cout << "copyZ "; }
    void act() override { cout << "Z.act "; }
    ~Z() override { cout << "~Z "; }
};

int main() {
    Z* pz = new Z{}; //it creates a Z object with a pointer to a Z object
    Y y;  //we have a Y object but the constructor is not called;
    X* px = pz; //so we have an object of type Z, but with a pointer to a X object
    px->act();  //act() is a virtual method => it will call the Z's act() method => Z.act
    y.use(*pz); //use(Y y) is not virtual, *pz is of static type Z and Z is a Y, so it matches the function Y::use(Y y) \
    parameter is passed by value, so the copy constructor is called => copyY Y.use \
    then the destructor is called because of the copyed object => ~Y, but Y class is inherited from X where the destructor is virtual, so this one is called as well => ~X
    delete pz;  //cals the Z's destructor because the destructor is virtual => ~Z ~Y ~X

    //the program ends and the cleanup will be called, so the destructor of Y will be called => ~Y ~X

    //output:
    //Z.act copyY Y.use ~Y ~X ~Z ~Y ~X ~Y ~X
    return 0;
}
