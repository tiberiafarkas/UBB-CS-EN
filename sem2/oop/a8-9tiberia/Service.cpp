#include "Service.h"
#include "Repository.h"
#include "FileRepository.h"
#include "HTMLRepo.h"
#include "CSVRepo.h"
#include "comand.h"

Service::Service() {
	this->movies = new FileRepository("movies.txt");
	this->watchlist = new FileRepository("watchlist.txt");
}

Service::~Service() {
	delete movies;
	delete watchlist;
}

void Service::addMovie(const Movie &movie) {
	try {
		this->movies->addMovie(movie);

		AddCommand* addCommand = new AddCommand(this->movies, this->watchlist, movie);
		this->undoRedoService.addCommand(addCommand);
	}
	catch (const DuplicateMovieException& e) {
		throw e;
	}
}

void Service::deleteMovie(const std::string& title) {
	try {
		this->movies->deleteMovie(title);
		try {
			this->watchlist->deleteMovie(title);
		}
		catch (const RepositoryException& e) {
		}

		DeleteCommand* deleteCommand = new DeleteCommand(this->movies, this->watchlist, this->getMovieByTitle(title));
		this->undoRedoService.addCommand(deleteCommand);
	}
	catch (const RepositoryException& e) {
		throw e;
	}
}

void Service::updateMovie(const Movie &movie) {
	try {
		this->movies->updateMovie(movie);

		Movie movie_from_watchlist = this->watchlist->getMovieByTitle(movie.getTitle());
		if (this->isMovieInWatchlist(movie_from_watchlist)) {
			this->watchlist->updateMovie(movie);
		}

		UpdateCommand* updateCommand = new UpdateCommand(this->movies, this->watchlist, this->getMovieByTitle(movie.getTitle()), movie);
		this->undoRedoService.addCommand(updateCommand);
	}
	catch (const RepositoryException& e) {
		throw e;
	}
}

std::vector<Movie> Service::getMovies() const {
	return this->movies->getMovies();
}

void Service::addMovieToWatchlist(const std::string title) {
	Movie movie = this->getMovieByTitle(title);

	if (movie.getTitle() == "") {
		throw RepositoryException("Movie does not exist!");
	}

	try {
		this->watchlist->addMovie(movie);
	}
	catch (const DuplicateMovieException& e) {
		throw e;
	}
}

std::vector<Movie> Service::getWatchlist() const {
	return this->watchlist->getMovies();
}

void Service::deleteMovieFromWatchlist(const std::string& title) {
	try {
		this->watchlist->deleteMovie(title);
	}
	catch (const RepositoryException& e) {
		throw e;
	}
}

bool Service::isMovieInWatchlist(const Movie& movie) {
	return this->watchlist->isMovieInWatchlist(movie);
}

Movie Service::getMovieByTitle(const std::string& title) {
	return this->movies->getMovieByTitle(title);
}

std::vector<Movie> Service::getMoviesByGenre(const std::string& genre) {
	std::vector<Movie> movies_by_genre;
	std::vector<Movie> all_movies = this->getMovies();
	
	for (auto movie : all_movies) {
		if (movie.getGenre() == genre) {
			movies_by_genre.push_back(movie);
		}
	}

	if (genre == "") {
		return all_movies;
	}

	return movies_by_genre;
}

void Service::setTypeOfRepository(const std::string type) {
	std::string file_name;
	if (type == "2") {
		this->watchlist = new HTMLRepo("watchlist.html");
		file_name = "watchlist.html";
	}
	else if (type == "1") {
		this->watchlist = new CSVRepo("watchlist.csv");
		file_name = "watchlist.csv";
	}
	else {
		this->watchlist = new FileRepository("watchlist.txt");
		file_name = "watchlist.txt";
	}

	ShellExecuteA(NULL, "open", file_name.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void Service::increaseLikes(const std::string& title) {
	Movie movie = this->getMovieByTitle(title);
	movie.setNumberOfLikes(movie.getNumberOfLikes() + 1);
	this->updateMovie(movie);
}

void Service::executeUndo() {
	this->undoRedoService.undo();
}

void Service::executeRedo() {
	this->undoRedoService.redo();
}