#include <iostream>
#include <string>
using namespace std;

template <typename T>
class elem
{
private:
	T x;
public:
	elem(T _x) : x{ _x } {}
	static T add(T a, T b) { return a + b; }
	elem& operator+=(const T& a) { x += a; return *this; }
	T get() { return x; }
};

int main()
{
	cout << elem<string>::add("answer to ", "life "); //answer to life
	elem<int> e{ 3 }; // x = 3
	e += 39; // x = 42
	cout << e.get(); // 42
	return 0;

	//output:
	//answer to life 42
}