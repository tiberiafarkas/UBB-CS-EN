#include <iostream>

using namespace std;

class A {
private:
	int *x;
public:
	A(int _x = 0) {
		x = new int{ _x };
	}
	A(const A& a) {
		x = new int{ *a.x };
	}
	int get() { return *x; } 
	void set(int _x) { *x = _x; }
	~A() { delete x; }
};

int main()
{
	A a1, a2; a1.set(8); //a1.x = 0 a2.x = 0 a1.x = 8 
	A a3; a3 = a1; //because the assignment operator is not defined, this will use the default\
	assignment operator which does a shallow copy so, both a1.x and a3.x will point to the \
	same memory location which will cause a double delete when the destructors are called.
	A a4 = a1; //this one is alright because it uses the copy constructor
	a1.set(5); //a1 = 5, a4 = 5
	cout << a1.get() << " "; //5
	cout << a2.get() << " "; //0
	cout << a3.get() << " "; //5
	cout << a4.get() << " "; //8

	//output:
	//5 0 5 8 then the program crashes

	//if you do \
	A a5 = a1; //this will use the copy constructor and a5 will have its own memory location \
	but if you do \
	A a3; \
	a3 = a1; //this will use the default assignment operator and a3 will point to the same memory location as a1

	return 0;
}