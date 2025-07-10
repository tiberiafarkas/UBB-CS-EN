#define _CRT_SECURE_NO_WARNINGS
#include "Material.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Material* createMaterial(char* name, char* supplier, int quantity, int day, int month, int year) {
	Material* material = (Material*)malloc(sizeof(Material));
	material->name = (char*)malloc(strlen(name) + 1);
	strcpy(material->name, name);
	
	material->supplier = (char*)malloc(strlen(supplier) + 1);
	strcpy(material->supplier, supplier);
	
	material->quantity = quantity;
	
	material->date.day = day;
	material->date.month = month;
	material->date.year = year;
	
	return material;
}

void DestroyMaterial(Material* material) {
	if (material == NULL)
		return;

	free(material->name);
	free(material->supplier);
	free(material);
}