#pragma once
#include "Repository.h"
#include <fstream>

class FileRepository : public Repository {
private:
	std::string filePath;
public:
	FileRepository(const std::string& filePath);
	void saveMovies();
	void loadMovies();
	std::string getFileName();
};