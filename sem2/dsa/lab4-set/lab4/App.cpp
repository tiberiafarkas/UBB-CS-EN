#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
#include <cassert>
using namespace std;

void test_union() {
	Set s1 = Set();
	s1.add(5);
	s1.add(2);
	s1.add(3);
	s1.add(11);

	Set s2 = Set();

	s1._union(s2);
	assert(s1.size() == 4);


	s2.add(1);
	s2.add(2);
	s2.add(3);
	s2.add(4);
	s2.add(18);

	s1._union(s2);
	
	assert(s1.size() == 7);
	assert(s1.search(5) == true);
	assert(s1.search(2) == true);
	assert(s1.search(18) == true);
	assert(s1.search(1) == true);

	SetIterator it = s2.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		assert(s1.search(e) == true);
		it.next();
	}

	cout << "Union test passed!" << endl;
}


int main() {
	test_union();
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");

}



