#pragma once
#include "DynamicArray.h"
#include "Movie.h"

class Repository {
private:
	DynamicArray<Movie> movies;
	DynamicArray<Movie> watchlist;

public:
	//constructor for the repository
	Repository();

	//destructor for the repository
	~Repository();

	//adds a movie to the repository
	//returns true if the movie was added, false otherwise
	bool addMovie(const Movie& movie);

	//deletes a movie from the repository
	//returns true if the movie was deleted, false otherwise
	bool deleteMovie(const std::string& title);

	//updates a movie from the repository
	//returns true if the movie was updated, false otherwise
	bool updateMovie(const Movie& movie);

	//returns the list of movies
	DynamicArray<Movie> getMovies() const;

	//adds a movie to the watchlist
	//returns true if the movie was added, false otherwise
	bool addMovieToWatchlist(const Movie& movie);

	//returns the watchlist
	DynamicArray<Movie> getWatchlist() const;

	//delete a movie from the watchlist
	//returns true if the movie was deleted, false otherwise
	bool deleteMovieFromWatchlist(const std::string& title);

	//return true if the movie is in the watchlist, false otherwise
	bool isMovieInWatchlist(const Movie& movie);

	//returns the movie with the given title
	Movie getMovieByTitle(const std::string& title);

};