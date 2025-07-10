#pragma once
#include "DynamicArray.h"
#include "School.h"

class Repository {
private:
	DynamicArray<School> schools;
	
public:
	bool add(School s);
	DynamicArray<School> getAll();
};