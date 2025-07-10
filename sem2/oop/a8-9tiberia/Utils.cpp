#include "Utils.h"
#include <sstream>

vector<string> tokenize(string input, char separator) {
	stringstream is{ input };
	vector<string> result;
	string token;

	while (getline(is, token, separator))
		result.push_back(token);

	return result;
}