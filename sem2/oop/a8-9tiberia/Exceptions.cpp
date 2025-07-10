#include "Exceptions.h"

const char* FileException::what() {
	return this->message.c_str();
}

const char* RepositoryException::what() {
	return this->message.c_str();
}

const char* DuplicateMovieException::what() {
	return "Movie already exists in the repository!";
}