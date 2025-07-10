#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//Given the test function below, specify and implement the function fct.

template<typename T> 
T fct(vector<T> v) {
	if (v.empty())
		throw exception();

	T maxi{};
	for (auto i : v) {
		maxi = max(maxi, i);
	}
	return maxi;
}

void testFct()
{
	vector<int> v1{ 4, 2, 1, 6, 3, -4 };
	assert(fct<int>(v1) == 6);
	vector<int> v2;
	try
	{
		fct<int>(v2);
		assert(false);
	}
	catch (std::exception&) { assert(true); }

	vector<double> v3{ 2, 10.5, 6.33, -100, 9, 1.212 };
	assert(fct<double>(v3) == 10.5);

	vector<string> v4{ "y", "q", "a", "m" };
	assert(fct<string>(v4) == "y");

	cout << "Well done!";
}

int main()
{
	testFct();
}

