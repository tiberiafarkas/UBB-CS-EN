#include <iostream>

using namespace std;

//determine the result of the execution of the following program \
if there are any errors, indicate the exact place where the errors occur

class B {
public:
	virtual void f() { cout << "B.f "; }
	virtual ~B() { cout << "~B "; }
};

class D : public B {
private:
	B& b;
public:
	D(B& _b) : b(_b) { cout << "D "; b.f(); }
	void f() override { cout << "D.f "; }
	~D() { cout << "~D "; }
};

int main() {
	B* b1 = new B{}; // new B object
	b1->f(); // B.f
	B* b2 = new D{ *b1 }; // new D object with pointer to B, it is called the constructor of D => D B.f
	b2->f(); //because the f() function is virtual, it will call D's f() method => D.f
	delete b2; //the destructor is virtual, so it calls the destructor of D's and after of B => ~D ~B
	delete b1; //calls the destructor of B => ~B
	return 0;

	//output:
	//B.f D B.f D.f ~D ~B ~B
}
