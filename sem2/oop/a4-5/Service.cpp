#include "Service.h"

Service::Service() {
	this->repo = Repository();
}

Service::~Service() {
}

bool Service::addMovieToRepository(const Movie& movie) {
	return this->repo.addMovie(movie);
}

bool Service::deleteMovieFromRepository(const std::string& title) {
	return this->repo.deleteMovie(title);
}

bool Service::updateMovieFromRepository(const Movie& movie) {
	return this->repo.updateMovie(movie);
}

DynamicArray<Movie> Service::getMovies() const {
	return this->repo.getMovies();
}

bool Service::addMovieToWatchlist(const Movie& movie) {
	return this->repo.addMovieToWatchlist(movie);
}

DynamicArray<Movie> Service::getWatchlist() const {
	return this->repo.getWatchlist();
}

bool Service::deleteMovieFromWatchlist(const std::string& title) {
	return this->repo.deleteMovieFromWatchlist(title);
}

bool Service::isMovieInWatchlist(const Movie& movie) {
	return this->repo.isMovieInWatchlist(movie);
}

Movie Service::getMovieByTitle(const std::string& title) {
	return this->repo.getMovieByTitle(title);
}

DynamicArray<Movie> Service::getMoviesByGenre(const std::string& genre) {
	DynamicArray<Movie> movies_by_genre = DynamicArray<Movie>();
	DynamicArray<Movie> all_movies = this->getMovies();

	for (int i = 0; i < all_movies.getSize(); ++i) {
		if (all_movies[i].getGenre() == genre) {
			movies_by_genre.add_movie(all_movies[i]);
		}
	}

	return movies_by_genre;
}