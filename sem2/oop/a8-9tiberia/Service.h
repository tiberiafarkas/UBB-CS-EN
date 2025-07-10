#pragma once
#include "Repository.h"
#include "windows.h"
#include "ComAdmin.h"
#include "comand.h"

class Service {
public:
	Repository *movies;
	Repository *watchlist;
	UndoRedoService undoRedoService;
public:

	//contructor for the service
	Service();

	//destructor for the service
	~Service();

	//adds a movie to the repository
	//returns true if the movie was added, false otherwise
	void addMovie(const Movie &movie);

	//deletes a movie from the repository
	//returns true if the movie was deleted, false otherwise
	void deleteMovie(const std::string& title);

	//updates a movie from the repository
	//returns true if the movie was updated, false otherwise
	void updateMovie(const Movie &movie);

	//returns the list of movies
	std::vector<Movie> getMovies() const;

	//adds a movie to the watchlist
	//returns true if the movie was added, false otherwise
	void addMovieToWatchlist(const std::string movie);

	//returns the watchlist
	std::vector<Movie> getWatchlist() const;

	//delete a movie from the watchlist
	//returns true if the movie was deleted, false otherwise
	void deleteMovieFromWatchlist(const std::string& title);

	//return true if the movie is in the watchlist, false otherwise
	bool isMovieInWatchlist(const Movie& movie);

	//returns the movie with the given title
	Movie getMovieByTitle(const std::string& title);

	//get movies by genre
	std::vector<Movie> getMoviesByGenre(const std::string& genre);

	//set the file name of the repository
	void setTypeOfRepository(const std::string type);

	//increase likes
	void increaseLikes(const std::string& title);

	void executeUndo();

	void executeRedo();
};