#include "Ui.h"
#include "Validator.h"
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
	std::cout << "5. See the watch list in default application" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

void UI::printMovies(const std::vector<Movie>& movies) {
	std::cout << "-------------------------------------\n";
	std::cout << "Movies:\n";
	for (auto movie: movies) {
		std::cout << "Title: " << movie.getTitle() << "\n";
		std::cout << "Genre: " << movie.getGenre() << "\n";
		std::cout << "Trailer: " << movie.getTrailer() << "\n";
		std::cout << "Year of release: " << movie.getYearOfRelease() << "\n";
		std::cout << "Number of likes: " << movie.getNumberOfLikes() << "\n";
		std::cout << "\n";
	}
	std::cout << "-------------------------------------\n";
}

void UI::printWatchlist(const std::vector<Movie>& watchList) {
	std::cout << "-------------------------------------\n";
	std::cout << "Watchlist:\n";
	for (auto movie: watchList) {
		std::cout << "Title: " << movie.getTitle() << "\n";
		std::cout << "Genre: " << movie.getGenre() << "\n";
		std::cout << "Trailer: " << movie.getTrailer() << "\n";
		std::cout << "Year of release: " << movie.getYearOfRelease() << "\n";
		std::cout << "Number of likes: " << movie.getNumberOfLikes() << "\n";
		std::cout << "\n";
	}
	std::cout << "-------------------------------------\n";
}

void UI::AdminAddMovie() {
	Movie movie;
	std::cout << "Enter the movie\n";
	std::cout << "The format of the input should look like: title,genre,yearOfRelease,numberOfLikes,trailer\n";
	std::cin.ignore();

	try {
		std::cin >> movie;
	}
	catch (MovieExceptions& e) {
		for ( const auto &argument: e.returnErrors())
		{
			std::cout << argument.what() << "\n";
		}
		return;
	}

	try {
		this->service.addMovie(movie);
	}
	catch (DuplicateMovieException &e) {
		std::cout << e.what() << "\n";
	}
}

void UI::AdminDeleteMovie() {
	std::string title;
	std::cout << "Delete movie\n";
	std::cout << "Title: ";
	std::cin.get();
	getline(std::cin, title);

	try {
		this->service.deleteMovie(title);
	}
	catch (RepositoryException &e) {
		std::cout << e.what() << "\n";
	}
}

void UI::AdminUpdateMovie() {
	Movie movie;
	std::cout << "Update movie\n";
	std::cout << "The format of the input should look like: title,genre,yearOfRelease,numberOfLikes,trailer\n";
	std::cin.ignore();

	try {
		std::cin >> movie;
	}
	catch (MovieExceptions& e) {
		for (auto argument : e.returnErrors())
		{
			std::cout << argument.what() << "\n";
		}
		return;
	}

	try {
		this->service.updateMovie(movie);
	}
	catch (RepositoryException &e) {
		std::cout << e.what() << "\n";
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
		this->service.addMovieToWatchlist(title);
	}
	catch (RepositoryException &e) {
		std::cout << e.what() << "\n";
	}
}

void UI::UserDeleteMovieFromWatchlist() {
	std::string title;
	std::cout << "Delete movie from watchlist\n";
	std::cout << "Title: ";
	std::cin.get();
	getline(std::cin, title);

	try {
		this->service.deleteMovieFromWatchlist(title);

		std::cout << "Did you like the movie? (yes/no): ";
		std::string answer;
		std::cin >> answer;
		
		if (answer == "yes") {
			Movie movie = this->service.getMovieByTitle(title);
			movie.setNumberOfLikes(movie.getNumberOfLikes() + 1);
			this->service.updateMovie(movie);
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
	std::vector<Movie> movies_by_genre = this->service.getMoviesByGenre(genre);

	if (movies_by_genre.size() == 0) {
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
				if (i == movies_by_genre.size()) {
					i = 0;
				}
				break;

			case 2:
				if (this->service.isMovieInWatchlist(movies_by_genre[i]) == false) {
					this->service.addMovieToWatchlist(movies_by_genre[i].getTitle());
				}
				else {
					std::cout << "Movie already in watchlist!" << "\n";
				}

				i++;
				if (i == movies_by_genre.size()) {
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

void UI::openWindowForWatchList() {
	std::cout << "What type of watchlist do you want to open?\n";
	std::cout << "1. csv\n2. html\n";
	std::string type;
	std::cout << "Enter type: ";
	std::cin >> type;
	std::string file_name;
	if (type == "1") {
		file_name = "watchlist.csv";
	}
	else if (type == "2") {
		file_name = "watchlist.html";
	}
	else {
		std::cout << "Invalid type!" << "\n";
		return;
	}

	//std::string url = "file:///" + file_name;
	ShellExecuteA(NULL, "open", file_name.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void UI::runUser() {

	while (true) {
		std::cout << "Choose the type of watchlist:\n";
		std::cout << "1. csv\n2. html\n3. file\n0. exit\n";
		std::string type;
		std::cout << "Enter type: ";
		std::cin >> type;
		std::cout << "\n";
		if (type == "0")
			return;
		if (type == "1" || type == "2" || type == "3") {
			this->service.setTypeOfRepository(type);
			break;
		}
		else {
			std::cout << "Invalid type!" << "\n";
		}
	}

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
		
		case 5:
			this->openWindowForWatchList();
			break;

		default:
			std::cout << "Invalid command!" << "\n";
			break;
		}
	}
}

void UI::start() {
	this->service.setTypeOfRepository("file");
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