#include <iostream>
#include <string>
using namespace std;

string except(int x)
{
	if (x < 0)
		throw string{ "Negative " };
	return "Positive ";
}

int main()
{
	cout << "One ";
	try
	{
		cout << except(3);  //positive
		cout << except(-2);  //throws exception
		cout << except(5);
	}
	catch (string& ex) { cout << ex << " "; } //catch the exception => Negative
	return 0;
}

//output:
//One Positive Negative