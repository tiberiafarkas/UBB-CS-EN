#pragma once
#include "Service.h"

class UI {
private:
	void printInitialMenu();
	void printAdminMenu();
	void printUserMenu();
	void printMovies(const std::vector<Movie>& movies);
	void printWatchlist(const std::vector<Movie>& watchlist);
	void AdminAddMovie();
	void AdminDeleteMovie();
	void AdminUpdateMovie();
	void runAdmin();
	void UserAddMovieToWatchlist();
	void UserDeleteMovieFromWatchlist();
	void printMoviesByGenre();
	void openWindowForWatchList();
	void runUser();

public:
	UI();
	~UI();
	Service service;
	void start();

};