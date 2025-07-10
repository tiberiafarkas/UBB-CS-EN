#include "FileRepository.h"
#include "Validator.h"

FileRepository::FileRepository(const std::string& filePath) : Repository(), filePath(filePath) {
	this->loadMovies();
}

void FileRepository::saveMovies() {
	std::ofstream fout(this->filePath);

	if (!fout.is_open()) {
		throw std::runtime_error("Could not open file");
	}
	for (const auto& movie : this->list_of_movies) {
		fout << movie;
	}
	fout.close();
}

void FileRepository::loadMovies() {
	std::ifstream fin(this->filePath);

	if (!fin.is_open()) {
		throw std::runtime_error("Could not open file");
	}
	
	Movie movie;
	
	while (true) {
		try {
			if (!(fin >> movie))
				break; // end of file or fail
			this->list_of_movies.push_back(movie);
		}
		catch (MovieExceptions& e) {
			// handle the error, e.g., log and skip
			throw;
		}
	}
	
	fin.close();
}

std::string FileRepository::getFileName() {
	return this->filePath;
}