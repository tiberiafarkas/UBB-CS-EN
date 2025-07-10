#pragma once
#include "Repository.h"

typedef struct {
	Repository* repo;
} Service;

Service* createService(Repository* repo);
void AddMaterialService(Service* service, Material* material);
Repository *GetMaterialsPastExpirationDate(Service* service, int *day, int *month, int *year, char *string);