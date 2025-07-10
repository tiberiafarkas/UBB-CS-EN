#pragma once
#include "Service.h"

class UI {
private:
	void printInitialMenu();
	void printAdminMenu();
	void printUserMenu();
	void printMovies(const DynamicArray<Movie>& movies);
	void printWatchlist(const DynamicArray<Movie>& watchlist);
	void AdminAddMovie();
	void AdminDeleteMovie();
	void AdminUpdateMovie();
	void runAdmin();
	void UserAddMovieToWatchlist();
	void UserDeleteMovieFromWatchlist();
	void printMoviesByGenre();
	void runUser();

public:
	UI();
	~UI();
	Service service;
	void start();

};