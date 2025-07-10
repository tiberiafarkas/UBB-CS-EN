#include <iostream>
#include <string>
using namespace std;

//Determine the result of the execution of the following program, if there are any errors\
indicate the exact place where the errors occur

template<typename T, typename U>
U fct2(T a, T b, U x, U y)
{
	cout << a << " ";
	cout << b << " ";
	if (a == b)
		return x + y;
	return x;
}

class A
{
	int a;
public:
	A(int _a) : a{ _a } {}
	/*
	* this part is used to fix the error, and yes, you need const A& obj in order to work
	A operator+(A& other) {
		return A(a + other.a);
	}
	friend ostream& operator<<(ostream& os, const A& obj) {
		return os << obj.a;
	}
	*/
};

int main()
{
	cout << fct2<int, int>(10, 10, 5, 5) << " "; //10 10 10
	cout << fct2<double, int>(10, 10.5, 5, 5) << " "; //10 10.5 5
	cout << fct2<int, string>(-2, -2, "Good ", "luck!"); //-2 -2 Goodluck!
	cout << fct2<int, A>(1, 1, A{ 2 }, A{ 3 }); //the class A does not define the operator +, so an error will ocurr
	return 0;
}

//output:
//10 10 10 10 10.5 5 -2 -2 Goodluck!