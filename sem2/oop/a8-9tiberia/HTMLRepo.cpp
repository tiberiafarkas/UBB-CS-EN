#include "HTMLRepo.h"
#include "Exceptions.h"
#include <fstream>

HTMLRepo::HTMLRepo(const std::string& fileName) : Repository(), fileName(fileName) {
	this->saveMovies();
}

void HTMLRepo::saveMovies() {
	std::ofstream fout(this->fileName);
	if (!fout.is_open()) {
		throw FileException("Could not open file");
	}
	fout << "<!DOCTYPE html>\n<html>\n<head>\n<title>Movie List</title>\n</head>\n<body>\n<table border=\"1\">\n<tr><td>Index<\td><td>Title</td><td>Genre</td><td>Year of Release</td><td>Number of Likes</td><td>Trailer</td></tr>\n";
	int index = 1;
	for (const auto& movie : this->list_of_movies) {
		fout << "<tr> <td>" << index++ <<  "</td> <td>" << movie.getTitle() << "</td> <td>" << movie.getGenre() << "</td> <td>" << movie.getYearOfRelease() << "</td> <td>" << movie.getNumberOfLikes() << "</td> <td>" << movie.getTrailer() << "</td> </tr>\n";
	}
	fout << "</table>\n</body>\n</html>";
	fout.close();
}

void HTMLRepo::loadMovies() {
}

std::string HTMLRepo::getFileName() {
	return this->fileName;
}