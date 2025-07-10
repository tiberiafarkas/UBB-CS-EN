//Determine the result of the execution of the following C++ programs.If there are any errors, indicate the exact place where the errors occur.Justify your answers.

#include <iostream>
using namespace std;

int except(bool ex)
{
	if (ex)
		throw 10;
	cout << "finished function." << '\n';
}

int main()
{
	cout << 1 << " ";
	try
	{
		cout << except(true) << " "; //throw an exception
		cout << except(5 < 5) << " ";
	}
	catch (int& ex) { cout << ex << " "; } //catch the exception => 10
	cout << 40 << " ";
	return 0;
}

//output:
//1 10 40