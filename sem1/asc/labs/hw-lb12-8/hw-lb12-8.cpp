// hw-lb12-8.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Show for each number from 32 to 126 the value of the number (in base 8) and the character with that ASCII code.

#include <stdio.h>

extern "C" char* base8(int number);

int main()
{
	char* number_b8;
	for (int i = 32; i <= 126; ++i) {
		number_b8 = base8(i);
		printf("the number %d in base 8 is %s and its ASCII character is %c\n", i, number_b8, (char)i);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
