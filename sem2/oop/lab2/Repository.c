#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Repository.h"

void AddMaterial(Repository* repo, Material* material) {
	repo->materials[repo->length] = material;
	repo->length++;
}

Repository* createRepository() {
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	repo->length = 0;
	return repo;
}

void DeleteMaterial(Repository *repo, char *name) {
	for (int i = 0; i < repo->length; i++) {
		if ( strcmp(repo->materials[i]->name, name) == 0 ) 
			DestroyMaterial(repo->materials[i]);
	}
	free(repo);
}

void UpdateMaterial(Repository* repo, char* name, char* supplier, int* quantity, int* day, int* month, int* year, Material *material) {
	for (int i = 0; i < repo->length; ++i) {
		if (strcmp(material->name, repo->materials[i]->name) == 0) {
			strcpy(repo->materials[i]->name, name);
			strcpy(repo->materials[i]->supplier, supplier);
			repo->materials[i]->quantity = *quantity;
			repo->materials[i]->date.day = *day;
			repo->materials[i]->date.month = *month;
			repo->materials[i]->date.year = *year;
		}
	}
}