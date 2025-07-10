#include "CSVRepo.h"
#include "Exceptions.h"
#include <fstream>


CSVRepo::CSVRepo(const std::string& fileName) : Repository(), fileName(fileName) {
	this->saveMovies();
}

void CSVRepo::saveMovies() {
	std::ofstream fout(this->fileName);
	if (!fout.is_open()) {
		throw FileException("Could not open file");
	}
	int index = 1;
	for (const auto& movie : this->list_of_movies) {
		fout << index++ << ", " << movie.getTitle() << ", " << movie.getGenre() << ", " << movie.getYearOfRelease() << ", " << movie.getNumberOfLikes() << ", " << movie.getTrailer() << "\n";
	}
	fout.close();
}

void CSVRepo::loadMovies() {
}

std::string CSVRepo::getFileName() {
	return this->fileName;
}