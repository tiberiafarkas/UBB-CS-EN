#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	vector<string> str{ "a", "b", "c", "d" };
	vector<string>::iterator it = str.end();
	it--;
	*it = "a"; //a b c a
	it--;
	//str.erase(it); // it produces an error because it deletes the iterator
	str.insert(it, "b"); // a b b c a
	for (it = str.begin(); it != str.end(); it++)
		cout << *it << " ";
	return 0;
}