#include <iostream>

using namespace std;

class B {
public:
	B() {}
	B(const B& b) { cout << "copy "; } 
	virtual void f() { cout << "B.f "; } 
	void g(B b) { cout << "B.g "; }; 
	virtual ~B() { cout << "~B "; }
};

class D : public B {
public:
	D() {}
	void f() { B::f(); cout << "D.f "; }
	void g(D d) { B::g(d); cout << "D.g "; }
};

int main() {
	/*
	D* t = new D{};
	t->g(*t); so it calls the D's f() method because t is an object of type D with pointer to D \
	because in g() the parameter is passed by value => creates a copy, D does not have any \
	copy constructor => it uses the one from B => copy \
	in B's g() method, the parameter is also passed by value => another copy => copy
	copy copy B.g ~B because the copy from the B's g() method will be destroyed
	D.g ~B because the copy from the G's g() method gets destroyed
	*/
	B* b = new B{}; //create an object of type B with pointer to B 
	B* d = new D{}; //create an object of type D with pointer to B
	d->f();	//f() is a virtual method, so it calls D's f() method => B.f D.f
	d->g(*b); //g() is not virtual, so it calls B's g(), but the parameter is passed by \
	value so it will make a copy => copy B.g ~B
	delete b; //~B
	delete d; //~B ~B because D has no destructor

	//output:
	//B.f D.f copy B.g ~B ~B ~B
	return 0;
}