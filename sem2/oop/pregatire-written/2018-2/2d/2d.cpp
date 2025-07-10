#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<string> str{ "a", "b", "c", "d" };
	str.erase(str.begin() + 2); // str {a, b, c}
	vector<string>::iterator it = str.begin();
	str.insert(it + 2, "b"); // str {a, b, b, c}
	str.insert(str.end() - 1, "a"); // str {a, b, b, a, c}
	str.pop_back(); // str {a, b, b, a}
	it = str.begin();
	while (it != str.end())
	{
		cout << *it << " "; // a b b a
		it++;
	}
	return 0;
}