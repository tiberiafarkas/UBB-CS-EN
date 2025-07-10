// lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "UI.h"

int main()
{
	Material* m1 = createMaterial("Material1", "Supplier1", 10, 1, 1, 2020);
	Material* m2 = createMaterial("Material2", "Supplier2", 20, 2, 2, 2020);
	Material* m3 = createMaterial("Material3", "Supplier3", 30, 3, 3, 2020);
	Material* m4 = createMaterial("Material4", "Supplier1", 15, 4, 4, 2020);
	Material* m5 = createMaterial("Material5", "Supplier2", 25, 5, 5, 2020);
	Material* m6 = createMaterial("Material6", "Supplier3", 35, 6, 6, 2020);
	Material* m7 = createMaterial("Material7", "Supplier1", 40, 1, 2, 2020);
	Material* m8 = createMaterial("Material8", "Supplier2", 50, 2, 3, 2020);
	Material* m9 = createMaterial("Material9", "Supplier4", 10, 3, 4, 2020);
	Material* m10 = createMaterial("Material10", "Supplier5", 20, 4, 5, 2020);

	Repository* repo = createRepository();
	Service* service = createService(repo);

	AddMaterial(repo, m1);
	AddMaterial(repo, m2);
	AddMaterial(repo, m3);
	AddMaterial(repo, m4);
	AddMaterial(repo, m5);
	AddMaterial(repo, m6);
	AddMaterial(repo, m7);
	AddMaterial(repo, m8);
	AddMaterial(repo, m9);
	AddMaterial(repo, m10);

	UI* ui = createUI(service);
	start(ui);
}
