#include <iostream>

using namespace std;

class B {
public:
	B() {}
	B(const B&) { cout << "copy "; }
	virtual B f() { cout << "B.f "; return *this; } 
	virtual ~B() { cout << "~B"; }
};

class D : public B {
private:
	B* b;
public:
	D(B* _b) : b{ _b } { cout << "D "; }
	B f() override {
		cout << "D.f "; return b->f(); //returns by valye -> copy constructor is called
	}
};

int main() {
	B* b = new B();
	B* d = new D{ b }; // D is created with a pointer to B => D
	d->f(); //D.f B.f copy ~B \
	the B's f() method returns a copy, so the D's f() method returns a copy of the B object \
	and the copy constructor is called and then the destructor of B is called
	delete d; //~B
	delete b; //~B
	return 0;

	/*
	Instead, if we would have:
	virtual B& f() { cout << "B.f "; return *this; }
	and
	virtual B& f() override {
		cout << "D.f "; return b->f(); //returns by reference -> no copy constructor is called
	}
	then the output would be:
	D.f B.f ~B ~B
	*/
}

