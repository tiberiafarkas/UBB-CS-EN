#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "UI.h"

void printMenu() {
	printf("1. Add material\n");
	printf("2. Delete material\n");
	printf("3. Update material\n");
	printf("4. See all available materials past their expiration date, containing a given string\n");
	printf("5. See all available materials\n");
	printf("0. Exit\n");
}

UI* createUI(Service* service) {
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->service = service;
	return ui;
}

void printMaterials(Repository* repo) {
	for (int i = 0; i < repo->length; ++i) {
		printf("Name: %s\n", repo->materials[i]->name);
		printf("Supplier: %s\n", repo->materials[i]->supplier);
		printf("Quantity: %d\n", repo->materials[i]->quantity);
		printf("Expiration date: %d.%d.%d\n", repo->materials[i]->date.day, repo->materials[i]->date.month, repo->materials[i]->date.year);
		printf("\n");
	}
}

void start(UI* ui) {
	while (1) {
		printMenu();
		int option;
		printf("Enter option: ");
		scanf("%d", &option);
		printf("\n");

		char name[100], supplier[100];
		int quantity, day, month, year;

		switch (option) {
		case 0:
			return;

		case 1:
			printf("Enter name: ");
			scanf("%s", name);
			printf("Enter supplier: ");
			scanf("%s", supplier);
			printf("Enter quantity: ");
			scanf("%d", &quantity);
			printf("Enter date dd.mm.yyyy: ");
			scanf("%d.%d.%d", &day, &month, &year);
			Material* material = createMaterial(name, supplier, quantity, day, month, year);
			AddMaterialService(ui->service, material);

			break;

		case 2:
			printf("Enter name: ");
			scanf("%s", name);
			DeleteMaterial(ui->service->repo, name);

			break;
		
		case 3:
			printf("Enter name: ");
			scanf("%s", name);
			printf("Enter new name: ");
			scanf("%s", name);
			printf("Enter new supplier: ");
			scanf("%s", supplier);
			printf("Enter new quantity: ");
			scanf("%d", &quantity);
			printf("Enter new date dd.mm.yyyy: ");
			scanf("%d.%d.%d", &day, &month, &year);
			Material* material2 = createMaterial(name, supplier, quantity, day, month, year);
			UpdateMaterial(ui->service->repo, name, supplier, &quantity, &day, &month, &year, material2);

			break;
		case 4:
			printf("Enter string: ");
			scanf("%s", name);
			printf("Enter date dd.mm.yyyy: ");
			scanf("%d.%d.%d", &day, &month, &year);
			Repository* repo = GetMaterialsPastExpirationDate(ui->service, &day, &month, &year, name);
			printMaterials(repo);

			break;

		case 5:
			printMaterials(ui->service->repo);
		}
	}
}