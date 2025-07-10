#pragma once

typedef struct {
	char* name;
	char* supplier;
	int quantity;
	struct {
		int day;
		int month;
		int year;
	} date;
} Material;

Material* createMaterial(char* name, char* supplier, int quantity, int day, int month, int year);
void DestroyMaterial(Material* material);