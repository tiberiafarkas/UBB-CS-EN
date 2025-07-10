#include <iostream>

using namespace std;

int fct(string v) {
    if (v == "") { 
        throw string{ "2" }; 
    }
    cout << "1 ";
    if (v.size() > 4) { 
        throw std::runtime_error{ "Not empty" }; 
    }
    return 0;
}

// prints: "1 0 1 Not empty"
int main() {
    try {
		cout << fct("Hi") << " "; //it prints 1 and it returns 0, so we have "1 0 "
		cout << fct("Hello") << " "; //it prints 1 and throw runtime_error, so we have "1 Not empty"
		cout << fct("") << " "; //it doesnt enter in the function because an error has been thrown before
    }
    catch (string& e) {
        cout << e;
    }
    catch (std::runtime_error& e) {
        cout << e.what();
    }
    return 0;
}