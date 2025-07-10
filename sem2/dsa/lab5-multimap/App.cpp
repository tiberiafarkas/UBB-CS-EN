#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"
#include <cassert>

using namespace std;

void testAddIfNotPresent() {
	MultiMap m1;
	m1.add(1, 2);
	m1.add(3, 4);
	m1.add(5, 6);
	MultiMap m2;
	m2.add(1, 2);
	m2.add(3, 4);
	m2.add(7, 8);
	int count = m1.addIfNotPresent(m2);
	assert(count == 1); // Only (7,8) should be added
	assert(m1.size() == 4); // Size should be 4 now

	MultiMapIterator it = m1.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		if (e.first == 1) {
			assert(e.second == 2);
		}
		else if (e.first == 3) {
			assert(e.second == 4);
		}
		else if (e.first == 5) {
			assert(e.second == 6);
		}
		else if (e.first == 7) {
			assert(e.second == 8);
		}
		it.next();
	}

	cout << "Test AddIfNotPresent passed!" << endl;
}


int main() {
	testAddIfNotPresent();
	testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}
