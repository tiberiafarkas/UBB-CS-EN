#include <iostream>
#include "adder.h"

using namespace std;

/*
Define the class Adder such that the following C++ code is correct and its result are the ones 
indicated in the comments.
*/

void function2() {
    Adder<int> add(5); //build a new Adder with initial value 5
    add = add + 5 + 2; //add valuess 5 and 2
    ++add; //adds the last added value (2) again
    add + 8; //add value 8
	cout << add.sum() << '\n'; //print sum, so far 22 (5 + 5 + 2 + 2 + 8 = 22)
    --add; //eliminate last added value
	cout << add.sum() << '\n'; //print modified sum, so far 14 (5 + 5 + 2 + 2 = 14)
	--(--add); //eliminate the last two added values
	cout << add.sum() << '\n'; //print modified sum, so far 10 (5 + 5 = 10)
    
    try {
        --(--(--add));
    }
    catch (runtime_error& ex) {
        cout << ex.what(); //prints "No more values!");
    }
}

int main()
{
	function2(); //call the function to test the Adder class
	return 0;
}
