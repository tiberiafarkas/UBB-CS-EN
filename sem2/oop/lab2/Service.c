#include "Service.h"
#include <stdio.h>
#include <stdlib.h>

Service* createService(Repository* repo) {
	Service* service = (Service*)malloc(sizeof(Service));
	service->repo = repo;
	return service;
}

void AddMaterialService(Service* service, Material* material) {
	//function that adds a material to the repository
	//it check if the material already exists in the repository and if so, increment the quantity
	for (int i = 0; i < service->repo->length; i++)
		if (strcmp(service->repo->materials[i]->name, material->name) == 0) {
			service->repo->materials[i]->quantity += material->quantity;
			return;
		}

	//otherwise, add the material to the repository
	AddMaterial(service->repo, material);
}

Repository *GetMaterialsPastExpirationDate(Service* service, int* day, int* month, int* year, char* string) {
	//function that returns a repository with all the materials that have the expiration date past the given date and contain the given string

	Repository* repo = createRepository();
	
	for (int i = 0; i < service->repo->length; ++i) {
		if (service->repo->materials[i]->date.year > *year || service->repo->materials[i]->date.year == *year && service->repo->materials[i]->date.month > *month ||
			service->repo->materials[i]->date.year == year && service->repo->materials[i]->date.month == *month && service->repo->materials[i]->date.day > *day) {
			if (strstr(service->repo->materials[i]->name, string)) {
				AddMaterial(repo, service->repo->materials[i]);
			}
		}
	}

	return repo;

}

