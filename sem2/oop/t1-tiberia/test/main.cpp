#include <iostream>
#include "ui.h"
#include "test.h"

int main()
{
	test t;
	t.testAll();
	UI ui;
	ui.run();
}