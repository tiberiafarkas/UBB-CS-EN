#include <iostream>

using namespace std;

class B {
public:
	B() {}
	B(const B&) {
		cout << "copy ";
	}
	virtual B f() {
		cout << "B.f "; 
		return *this;
	}
	virtual ~B() { cout << "~B "; }
};

class D : public B
{
private:
	B* b;
public:
	D(B* _b) : b{ _b } { cout << "D "; } 
	B f() override {
		cout << "D.f "; 
		return b->f();
	}
};

int main()
{
	B* b = new B(); //an object of type B with pointer to B, calls the B's constructor
	B* d = new D{ b }; //an object of type D with pointer to B, calls the D's constructor 
	d->f(); //f is a virtual function, so it calls D's f => D.f and calls B's f => B.f \
	however, B's f returns a copy of B, not a reference, so the copy constructor of B is called \
	=> copy and then the destructor of B is called => ~B
	delete d; //this calls the destructor of D, which calls the destructor of B \
	=> ~B ~B 
	delete b; //this calls the destructor of B => ~B

	//output:
	//D D.f B.f copy ~B ~B ~B
	return 0;
}