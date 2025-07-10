#pragma once
#include "Material.h"

typedef struct {
	Material *materials[100];
	int length;
} Repository;

Repository *createRepository();
void AddMaterial(Repository* repo, Material* material);
void DeleteMaterial(Repository* repo, char* name);
void UpdateMaterial(Repository* repo, char* name, char *suppplier, int *quantity, int *day, int *month, int *year, Material* material);