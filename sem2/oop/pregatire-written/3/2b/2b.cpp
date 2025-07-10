#include <iostream>

using namespace std;

class A {
private:
	int* x;
public:
	static int noOfInstances;

	A(int _x = 5) { //A a1 is the same as A a1(5);
		x = new int{ _x };
		noOfInstances++;
	}

	int get() { return *x; }
	void set(int _x) { *x = _x; } 

	~A() { delete x; }
};

int A::noOfInstances = 0;

int main() {
	A a1, a2; //default constructor called, noOfInstances = 2, a1.x and a2.x point to different memory locations \
	a1.x = 5 , a2.x = 5
	cout << a1.noOfInstances << " "; //2
	A a3 = a1; //no copy constructor made, shallow copy => both a1 and a3 point to the \
	same memory location => it will cause problems when one of them is destroyed and the\
	destructor tryes to delete the same memory location twice \
	because it uses the default copy constructor, my class doesnt manually increment noOfInstances
	cout << A::noOfInstances << " "; //2
	a1.set(10);
	cout << a1.get() << " "; //10
	cout << a2.get() << " "; //5
	cout << a3.get() << " "; //10

	//output:
	//2 2 10 5 10 and it crashes 
	return 0;
}