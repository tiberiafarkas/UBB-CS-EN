#include <iostream>

using namespace std;

class B {
public:
    B() {}
    B(const B& b) { cout << "copy "; }
    virtual void f() { cout << "B.f "; }
    void g(B b) { cout << "B.g "; }
    virtual ~B() { cout << "~B "; }
};

class D : public B {
public:
    D() {}
    void f() { B::f(); cout << "D.f "; }
    void g(D d) { B::g(d); cout << "D.g "; }
};

int main() {
	B* b = new B{}; // Create a B object, calls B's constructor which is empty so no printing
	B* d = new D{}; // Create a D object, but it is pointed to by a B pointer, D's constructor is called, which is empty and also B's constructor is called, so no printing
	d->f(); // We get into D f() where we call B's f() method and will print "B.f D.f " because B's f() is virtual, do dynamic dispatched is used
	d->g(*b); //g() is not virtual, so dispatch is based on the type of the pointer, which is B, so B's g() is called, and it prints "B.g ", *b is passed by value, so B's copy constructor is called,\
	 which prints "copy " but the temporary object created by the copy constructor has its own lifetime and it is destroyed at the end of the expression, so the destructor of B is called, printing "~B "
	delete b; // Delete the B object, which will call the destructor of B, printing "~B "
	delete d; // Delete the D object, the destructor of D is not defined, so it will call the destructor of B, printing "~B " again

	//output:
	//B.f D.f copy B.g ~B ~B ~B

    return 0;
}