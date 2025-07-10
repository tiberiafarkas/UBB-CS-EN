#pragma once
#include "Repository.h"

class CSVRepo : public Repository {
private:
	std::string fileName;
public:	
	CSVRepo(const std::string& fileName);
	void saveMovies();
	void loadMovies();
	std::string getFileName();
};