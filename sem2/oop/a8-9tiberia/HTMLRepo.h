#pragma once
#include "Repository.h"

class HTMLRepo : public Repository {
private:
	std::string fileName;

public:
	HTMLRepo(const std::string& fileName);
	void saveMovies();
	void loadMovies();
	std::string getFileName();
};