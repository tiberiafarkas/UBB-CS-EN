#pragma once
#include "Repository.h"

class Service {
private:
	Repository repo;

public:

	//contructor for the service
	Service();

	//destructor for the service
	~Service();

	//adds a movie to the repository
	//returns true if the movie was added, false otherwise
	bool addMovieToRepository(const Movie &movie);

	//deletes a movie from the repository
	//returns true if the movie was deleted, false otherwise
	bool deleteMovieFromRepository(const std::string& title);

	//updates a movie from the repository
	//returns true if the movie was updated, false otherwise
	bool updateMovieFromRepository(const Movie &movie);

	//returns the list of movies
	DynamicArray<Movie> getMovies() const;

	//adds a movie to the watchlist
	//returns true if the movie was added, false otherwise
	bool addMovieToWatchlist(const Movie &movie);

	//returns the watchlist
	DynamicArray<Movie> getWatchlist() const;

	//delete a movie from the watchlist
	//returns true if the movie was deleted, false otherwise
	bool deleteMovieFromWatchlist(const std::string& title);

	//return true if the movie is in the watchlist, false otherwise
	bool isMovieInWatchlist(const Movie& movie);

	//returns the movie with the given title
	Movie getMovieByTitle(const std::string& title);

	//get movies by genre
	DynamicArray<Movie> getMoviesByGenre(const std::string& genre);

};