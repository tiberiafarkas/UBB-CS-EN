#include "Ui.h"
#include <iostream>
#include <string>
#include <cassert>
#include <windows.h>
#include <shellapi.h>

UI::UI() {
	this->service = Service();
}

UI::~UI() {
}

void UI::printInitialMenu() {
	std::cout << "1. Admin mode" << std::endl;
	std::cout << "2. User mode" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

void UI::printAdminMenu() {
	std::cout << "1. Add movie" << std::endl;
	std::cout << "2. Delete movie" << std::endl;
	std::cout << "3. Update movie" << std::endl;
	std::cout << "4. See movies" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

void UI::printUserMenu() {
	std::cout << "1. Add movie to watchlist" << std::endl;
	std::cout << "2. Delete movie from watchlist" << std::endl;
	std::cout << "3. See the watch list" << std::endl;
	std::cout << "4. See movies by genre" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

void UI::printMovies(const DynamicArray<Movie>& movies) {
	std::cout << "-------------------------------------\n";
	std::cout << "Movies:\n";
	for (int i = 0; i < movies.getSize(); ++i) {
		std::cout << "Title: " << movies[i].getTitle() << "\n";
		std::cout << "Genre: " << movies[i].getGenre() << "\n";
		std::cout << "Trailer: " << movies[i].getTrailer() << "\n";
		std::cout << "Year of release: " << movies[i].getYearOfRelease() << "\n";
		std::cout << "Number of likes: " << movies[i].getNumberOfLikes() << "\n";
		std::cout << "\n";
	}
	std::cout << "-------------------------------------\n";
}

void UI::printWatchlist(const DynamicArray<Movie>& watchList) {
	std::cout << "-------------------------------------\n";
	std::cout << "Watchlist:\n";
	for (int i = 0; i < watchList.getSize(); ++i) {
		std::cout << "Title: " << watchList[i].getTitle() << "\n";
		std::cout << "Genre: " << watchList[i].getGenre() << "\n";
		std::cout << "Trailer: " << watchList[i].getTrailer() << "\n";
		std::cout << "Year of release: " << watchList[i].getYearOfRelease() << "\n";
		std::cout << "Number of likes: " << watchList[i].getNumberOfLikes() << "\n";
		std::cout << "\n";
	}
	std::cout << "-------------------------------------\n";
}

void UI::AdminAddMovie() {
	std::string title, genre, trailer;
	int yearOfRelease, numberOfLikes;
	std::cout << "Add movie\n";
	std::cout << "Title: ";
	std::cin.get();
	getline(std::cin, title);

	if (title.empty()) {
		std::cout << "Error: Title cannot be empty!\n";
		return;
	}

	std::cout << "Genre: ";
	getline(std::cin, genre);

	if (genre.empty()) {
		std::cout << "Error: Genre cannot be empty!\n";
		return;
	}

	std::cout << "Trailer: ";
	getline(std::cin, trailer);

	if (trailer.empty()) {
		std::cout << "Error: Trailer cannot be empty!\n";
		return;
	}

	std::cout << "Year of release: ";

	while (!(std::cin >> yearOfRelease) || yearOfRelease <= 1800 || yearOfRelease > 2100) {
		std::cout << "Error: Invalid year! Enter a valid year (1800-2100): ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	std::cout << "Number of likes: ";

	while (!(std::cin >> numberOfLikes) || numberOfLikes < 0) {
		std::cout << "Error: Invalid number of likes! Enter a non-negative integer: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	Movie movie = Movie(title, genre, yearOfRelease, numberOfLikes, trailer);

	try {
		if (this->service.addMovieToRepository(movie) == false) {
			throw std::exception();
		}
	}
	catch (std::exception& e) {
		std::cout << "\nMovie already exists!" << "\n";
	}
}

void UI::AdminDeleteMovie() {
	std::string title;
	std::cout << "Delete movie\n";
	std::cout << "Title: ";
	std::cin.get();
	getline(std::cin, title);

	/*if (title.empty()) {
		std::cout << "Error: Title cannot be empty!\n";
		return;
	}*/

	try {
		if (this->service.deleteMovieFromRepository(title) == false) {
			throw std::exception();
		}
	}
	catch (std::exception& e) {
		std::cout << "\nMovie does not exist!" << "\n";
	}
}

void UI::AdminUpdateMovie() {
	std::string title, genre, trailer;
	int yearOfRelease, numberOfLikes;
	std::cout << "Update movie\n";
	std::cout << "Title: ";
	std::cin.get();
	getline(std::cin, title);

	if (title.empty()) {
		std::cout << "Error: Title cannot be empty!\n";
		return;
	}

	std::cout << "New genre: ";
	getline(std::cin, genre);

	if (genre.empty()) {
		std::cout << "Error: Genre cannot be empty!\n";
		return;
	}

	std::cout << "New trailer: ";
	getline(std::cin, trailer);

	if (trailer.empty()) {
		std::cout << "Error: Trailer cannot be empty!\n";
		return;
	}

	std::cout << "New year of release: ";
	while (!(std::cin >> yearOfRelease) || yearOfRelease <= 1800 || yearOfRelease > 2100) {
		std::cout << "Error: Invalid year! Enter a valid year (1800-2100): ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	std::cout << "New number of likes: ";
	while (!(std::cin >> numberOfLikes) || numberOfLikes < 0) {
		std::cout << "Error: Invalid number of likes! Enter a non-negative integer: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	Movie movie = Movie(title, genre, yearOfRelease, numberOfLikes, trailer);

	try {
		if (this->service.updateMovieFromRepository(movie) == false) {
			throw std::exception();
		}
	}
	catch (std::exception& e) {
		std::cout << "\nMovie does not exist!" << "\n";
	}
}

void UI::runAdmin() {
	while (true) {
		this->printAdminMenu();
		int command;
		std::cout << "Enter command: ";
		std::cin >> command;
		std::cout << "\n";

		if (command == 0) {
			break;
		}

		switch (command) {
		case 1:
			this->AdminAddMovie();
			break;

		case 2:
			this->AdminDeleteMovie();
			break;

		case 3:
			this->AdminUpdateMovie();
			break;

		case 4:
			this->printMovies(this->service.getMovies());
			break;

		default:
			std::cout << "Invalid command!" << "\n";
			break;
		}
	}
}

void UI::UserAddMovieToWatchlist() {
	std::string title;
	std::cout << "Add movie to watchlist\n";
	std::cout << "Title: ";
	std::cin.get();
	getline(std::cin, title);

	if (title.empty()) {
		std::cout << "Error: Title cannot be empty!\n";
		return;
	}

	Movie movie = this->service.getMovieByTitle(title);
	if (movie.getTitle() == "") {
		std::cout << "Error: Movie does not exist!\n";
		return;
	}
	try {
		if (this->service.addMovieToWatchlist(movie) == false) {
			throw std::exception();
		}
	}
	catch (std::exception& e) {
		std::cout << "\nMovie does not exist or it has already been added to the WatchList!\n" << "\n";
	}
}

void UI::UserDeleteMovieFromWatchlist() {
	std::string title;
	std::cout << "Delete movie from watchlist\n";
	std::cout << "Title: ";
	std::cin.get();
	getline(std::cin, title);

	if (title.empty()) {
		std::cout << "Error: Title cannot be empty!\n";
		return;
	}

	try {
		if (this->service.deleteMovieFromWatchlist(title) == false) {
			throw std::exception();
		}

		std::cout << "Did you like the movie? (yes/no): ";
		std::string answer;
		std::cin >> answer;

		if (answer == "yes") {
			Movie movie = this->service.getMovieByTitle(title);
			movie.setNumberOfLikes(movie.getNumberOfLikes() + 1);
			this->service.updateMovieFromRepository(movie);
		}
	}
	catch (std::exception& e) {
		std::cout << "\nMovie does not exist!" << "\n";
	}
}

void UI::printMoviesByGenre() {
	std::string genre;
	std::cout << "Enter genre: ";
	std::cin.get();
	getline(std::cin, genre);
	DynamicArray<Movie> movies_by_genre = this->service.getMoviesByGenre(genre);

	if (movies_by_genre.getSize() == 0) {
		std::cout << "No movies with this genre!" << "\n";
	}
	else {
		std::cout << "-------------------------------------\n";
		int i = 0;
		while (true) {
			std::cout << "Current Movie:\n";
			std::cout << "Title: " << movies_by_genre[i].getTitle() << "\n";
			std::cout << "Genre: " << movies_by_genre[i].getGenre() << "\n";
			std::cout << "Trailer: " << movies_by_genre[i].getTrailer() << "\n";
			std::cout << "Year of release: " << movies_by_genre[i].getYearOfRelease() << "\n";
			std::cout << "Number of likes: " << movies_by_genre[i].getNumberOfLikes() << "\n";
			std::cout << "\n";

			std::string url = movies_by_genre[i].getTrailer();
			ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);


			std::cout << "1. Next" << "\n";
			std::cout << "2. Add to watchlist" << "\n";
			std::cout << "0. Exit" << "\n";

			int command;
			std::cout << "Enter command: ";
			std::cin >> command;
			std::cout << "\n";

			if (command == 0) {
				break;
			}

			switch (command) {
			case 1:
				i++;
				if (i == movies_by_genre.getSize()) {
					i = 0;
				}
				break;

			case 2:
				if (this->service.isMovieInWatchlist(movies_by_genre[i]) == false) {
					this->service.addMovieToWatchlist(movies_by_genre[i]);
				}
				else {
					std::cout << "Movie already in watchlist!" << "\n";
				}

				i++;
				if (i == movies_by_genre.getSize()) {
					i = 0;
				}
				break;

			default:
				std::cout << "Invalid command!" << "\n";
				break;
			}
		}
	}
}

void UI::runUser() {
	while (true) {
		this->printUserMenu();
		int command;
		std::cout << "Enter command: ";
		std::cin >> command;
		std::cout << "\n";

		if (command == 0) {
			break;
		}

		switch (command) {
		case 1:
			this->UserAddMovieToWatchlist();
			break;

		case 2:
			this->UserDeleteMovieFromWatchlist();
			break;

		case 3:
			this->printWatchlist(this->service.getWatchlist());
			break;

		case 4:
			this->printMoviesByGenre();
			break;

		default:
			std::cout << "Invalid command!" << "\n";
			break;
		}
	}
}

void UI::start() {
	while (true) {
		this->printInitialMenu();
		int command;
		std::cout << "Enter command: ";
		std::cin >> command;
		std::cout << "\n";

		if (command == 0) {
			break;
		}

		switch (command) {
		case 1:
			this->runAdmin();
			break;

		case 2:
			this->runUser();
			break;

		default:
			std::cout << "Invalid command!" << "\n";
			break;
		}
	}
}