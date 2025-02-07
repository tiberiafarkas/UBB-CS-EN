// hw-lb12-22.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

//It is given a number in base 2 represented on 32 bits. Write to the console the number in base 16. (use the quick conversion)

//function declared in asm file
extern "C" char* conversion(int number_b2);

int main()
{
	char binary_input[33]; // Buffer to hold up to 32 bits + null terminator
	int number_b2;
	char* number_b16;
	printf("Number in base 2: ");
	scanf("%32s", binary_input);

	number_b2 = (int)strtol(binary_input, NULL, 2);

	number_b16 = conversion(number_b2);
	printf("The number in b16 is: %s", number_b16);
	return 0;
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
