#include "Repository.h"

Repository::Repository() {
	this->movies = DynamicArray<Movie>();
	this->watchlist = DynamicArray<Movie>();
}

Repository::~Repository() {
}

bool Repository::addMovie(const Movie& movie) {
	for (int i = 0; i < this->movies.getSize(); ++i) {
		if (this->movies[i].getTitle() == movie.getTitle()) {
			return false;
		}
	}

	this->movies.add_movie(movie);
	return true;

}

bool Repository::deleteMovie(const std::string& title) {
	int ok = 0;
	for (int i = 0; i < this->movies.getSize(); ++i) {
		if (this->movies[i].getTitle() == title) {
			this->movies.delete_movie(i);
			ok = 1;
		}

		if (this->watchlist[i].getTitle() == title) {
			this->watchlist.delete_movie(i);
		}
	}

	if (ok == 1)
		return true;

	return false;
}

bool Repository::updateMovie(const Movie& movie) {
	bool ok = 0;

	for (int i = 0; i < this->movies.getSize(); ++i) {
		if (this->movies[i].getTitle() == movie.getTitle()) {
			this->movies[i] = movie;
			ok = 1;
		}

		if (this->watchlist[i].getTitle() == movie.getTitle()) {
			this->watchlist[i] = movie;
		}
	}

	if (ok == 1)
		return true;

	return false;
}

DynamicArray<Movie> Repository::getMovies() const {
	return this->movies;
}

bool Repository::addMovieToWatchlist(const Movie& movie) {
	for (int i = 0; i < this->watchlist.getSize(); ++i) {
		if (this->watchlist[i].getTitle() == movie.getTitle()) 
			return false;
		
	}
	this->watchlist.add_movie(movie);
	return true;
}

DynamicArray<Movie> Repository::getWatchlist() const {
	return this->watchlist;
}

bool Repository::deleteMovieFromWatchlist(const std::string& title) {
	for (int i = 0; i < this->watchlist.getSize(); ++i) {
		if (this->watchlist[i].getTitle() == title) {
			this->watchlist.delete_movie(i);
			return true;
		}
	}

	return false;
}

bool Repository::isMovieInWatchlist(const Movie& movie) {
	for (int i = 0; i < this->watchlist.getSize(); ++i) {
		if (this->watchlist[i].getTitle() == movie.getTitle()) 
			return true;
		
	}
	return false;
}

Movie Repository::getMovieByTitle(const std::string& title) {
	for (int i = 0; i < this->movies.getSize(); ++i) {
		if (this->movies[i].getTitle() == title) {
			return this->movies[i];
		}
	}
	return Movie();
}