#include "Repository.h"

Repository::Repository() {
	this->list_of_movies = std::vector<Movie>();
}

Repository::~Repository() {
}

void Repository::addMovie(const Movie& movie) {
	if (find(this->list_of_movies.begin(), this->list_of_movies.end(), movie) != this->list_of_movies.end())
		throw DuplicateMovieException();

	this->list_of_movies.push_back(movie);
	this->saveMovies();
}

void Repository::deleteMovie(const std::string& title) {
	int pos = -1, pos2 = -1;
	
	for (auto &movie : this->list_of_movies) {
		if (movie.getTitle() == title) {
			pos = find(this->list_of_movies.begin(), this->list_of_movies.end(), movie) - this->list_of_movies.begin();
			break;
		}
	}

	if (pos != -1) {
		this->list_of_movies.erase(this->list_of_movies.begin() + pos);
	}
	else {
		throw RepositoryException("Movie not found in repository");
	}

	this->saveMovies();
}

void Repository::updateMovie(const Movie& movie) {
	bool ok = 0;

	for (auto &el: this->list_of_movies) {
		if (el.getTitle() == movie.getTitle()) {
			el = movie;
			ok = 1;
		}
	}

	if (!ok)
		throw RepositoryException("Movie not found in repository");

	this->saveMovies();
}

std::vector<Movie> Repository::getMovies() const {
	return this->list_of_movies;
}

bool Repository::isMovieInWatchlist(const Movie& movie) {
	return find(this->list_of_movies.begin(), this->list_of_movies.end(), movie) != this->list_of_movies.end();
}

Movie Repository::getMovieByTitle(const std::string& title) {
	for (auto &movie : this->list_of_movies) {
		if (movie.getTitle() == title)
			return movie;
	}
	return Movie();
}