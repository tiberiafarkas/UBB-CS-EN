#include <iostream>
using namespace std;

class B
{
public:
	virtual void f() { cout << "B.f "; }
	virtual ~B() { cout << "~B "; }
};

class D : public B
{
private:
	B& b;
public:
	D(B* b) : b(*b) {}
	void f() override { b.f(); cout << "D.f "; }
	virtual ~D() { cout << "~D "; }
};

int main()
{
	B* b1 = new B{}; //creates a new B object with pointer to B
	b1->f(); //calls the B's f() method => B.f
	B* b2 = new D{ b1 }; //creates a new D object with pointer to B and calls the \
	the constructor of D's, which instantiates an object of type B but which is a reference\
	so it doesn't create a new object
	b2->f(); //f() is a virtual function so it calls D's f() method => B.f D.f
	delete b2;	//it deletes the D object and calls the destructor of B 1 times because \
	the pointer is of type B and inside the D class, but the B object which is inside of class D \
	is a reference => ~D ~B
	delete b1; // ~B
	return 0;

	//output:
	//B.f B.f D.f ~D ~B ~B

	//if the class D would have been:
	/*
	class D : public B
	{
	private:
		B b;
	public:
		D(B* b) : b(*b) {}
		void f() override { b.f(); cout << "D.f "; }
		virtual ~D() { cout << "~D "; }
	};

	Then when B* b2 = new D{b1} is called a new object of B will be created, which means
	that the both constructors of B will be called
	
	output:
	B.f B.f D.f ~D ~B ~B ~B

	for such a code:

	class B
	{
	public:
		B() { cout << "B "; }
		virtual void f() { cout << "B.f "; }
		virtual ~B() { cout << "~B "; }
	};

	class D : public B
	{
	private:
		B b;
	public:
		D(B* b) : b(*b) { cout << "D "; }
		void f() override { b.f(); cout << "D.f "; }
		virtual ~D() { cout << "~D "; }
	};

	B* b1 = new B{};
	b1 -> f();
	B* b2 = new D{b1};
	b2 -> f();
	delete b2;
	delete b1;

	the output is:
	B B.f B D B.f D.f ~D ~B ~B ~B
	*/
}

