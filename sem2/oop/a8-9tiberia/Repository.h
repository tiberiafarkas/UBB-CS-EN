#pragma once
#include "DynamicArray.h"
#include "Movie.h"
#include "Exceptions.h"
#include <vector>

class Repository {
protected:
	std::vector<Movie> list_of_movies;

public:
	//constructor for the repository
	Repository();

	//destructor for the repository
	~Repository();

	//adds a movie to the repository
	//returns true if the movie was added, false otherwise
	virtual void addMovie(const Movie& movie);

	//deletes a movie from the repository
	//returns true if the movie was deleted, false otherwise
	virtual void deleteMovie(const std::string& title);

	//updates a movie from the repository
	//returns true if the movie was updated, false otherwise
	virtual void updateMovie(const Movie& movie);

	//returns the list of movies
	std::vector<Movie> getMovies() const;

	//return true if the movie is in the watchlist, false otherwise
	bool isMovieInWatchlist(const Movie& movie);

	//returns the movie with the given title
	Movie getMovieByTitle(const std::string& title);

	//save the movies to the repository
	virtual void saveMovies() = 0;

	//load the movies from the repository
	virtual void loadMovies() = 0;

	//returns the file name of the repository
	virtual std::string getFileName() = 0;

};