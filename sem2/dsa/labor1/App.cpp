#include "ExtendedTest.h"
#include "ShortTest.h"
#include "NewTest.h"

#include "FixedCapBiMap.h"



#include <iostream>
using namespace std;


int main() {
	testRemoveCurrent();
	testAll();
	testAllExtended();
	

	cout << "That's all!" << endl;
	//system("pause");
	return 0;
}


