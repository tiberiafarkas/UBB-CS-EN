#include <iostream>

using namespace std;

class A {
private:
	int* x;
public:
	static int noOfInstances;
	A(int _x = 0) {
		x = new int{ _x };
		noOfInstances++;
	}
	int get() { return *x; }
	void set(int _x) { *x = _x; } 
	~A() { delete x; }
};

int A::noOfInstances = 0;

int main()
{
	A a1, a2; //a1.x = 0 a2.x = 0 
	cout << a1.noOfInstances << " "; //2 
	A a3 = a1; //the default copy constructor is called => creates shallow copy \
	a3 and a4 share the same memory => problems when deleting
	cout << A::noOfInstances << " "; //2
	a1.set(8);
	cout << a1.get() << " "; //8
	cout << a2.get() << " "; //0
	cout << a3.get() << " "; //8
	return 0;
}