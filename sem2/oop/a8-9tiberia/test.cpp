#include <cassert>
#include "Movie.h"
#include "Repository.h"
#include "Service.h"
#include <iostream>

class MockRepository : public Repository {
public:
    void saveMovies() override {}
    void loadMovies() override {}
    std::string getFileName() override { return "mock.txt"; }
};

class MockService : public Service {
public:
	MockService() {
		this->movies = new MockRepository();
		this->watchlist = new MockRepository();
	}
};

void testMovie() {
    Movie m;
    assert(m.getTitle() == "");
    assert(m.getGenre() == "");
    assert(m.getYearOfRelease() == 0);
    assert(m.getNumberOfLikes() == 0);
    assert(m.getTrailer() == "");

    Movie m2("Inception", "Sci-Fi", 2010, 1000000, "https://trailer.com");
    assert(m2.getTitle() == "Inception");
    assert(m2.getGenre() == "Sci-Fi");
    assert(m2.getYearOfRelease() == 2010);
    assert(m2.getNumberOfLikes() == 1000000);
    assert(m2.getTrailer() == "https://trailer.com");

	m2.setGenre("Action");
	m2.setNumberOfLikes(2000000);
	assert(m2.getGenre() == "Action");
	assert(m2.getNumberOfLikes() == 2000000);
	m2.setTrailer("https://new-trailer.com");
	assert(m2.getTrailer() == "https://new-trailer.com");
	m2.setTitle("New Title");
	assert(m2.getTitle() == "New Title");
	m2.setYearOfRelease(2021);
	assert(m2.getYearOfRelease() == 2021);

	Movie m3 = m2;
	assert(m3.getTitle() == "New Title");

	m3 = m3;
	assert(m3.getTitle() == "New Title");
}

void testRepository() {
	MockRepository repo;
	Movie m("Inception", "Sci-Fi", 2010, 1000000, "https://trailer.com");
	
	repo.addMovie(m);
	assert(repo.getMovies().size() == 1);
	assert(repo.getMovies()[0].getTitle() == "Inception");
	try {
		repo.addMovie(m);
	}
	catch (const DuplicateMovieException&) {
		assert(true);
	}
	
	repo.deleteMovie("Inception");
	assert(repo.getMovies().size() == 0);

	try {
		repo.deleteMovie("Inception");
	}
	catch (const RepositoryException&) {
		assert(true);
	}
	
	Movie m2("Avatar", "Sci-Fi", 2009, 2000000, "https://trailer.com");
	
	repo.addMovie(m2);
	assert(repo.getMovies().size() == 1);
	assert(repo.getMovies()[0].getTitle() == "Avatar");
	
	repo.updateMovie(Movie("Avatar", "Action", 2005, 19857, "https://trailer1.com"));
	assert(repo.getMovies()[0].getGenre() == "Action");
	assert(repo.getMovies()[0].getNumberOfLikes() == 19857);
	assert(repo.getMovies()[0].getYearOfRelease() == 2005);
	assert(repo.getMovies()[0].getTrailer() == "https://trailer1.com");
	assert(repo.getMovies()[0].getTitle() == "Avatar");
	assert(repo.getMovieByTitle("Avatar").getTitle() == "Avatar");
	assert(repo.getMovieByTitle("Avatar").getGenre() == "Action");
	assert(repo.getMovieByTitle("Avatar").getYearOfRelease() == 2005);
	assert(repo.getMovieByTitle("Avatar").getNumberOfLikes() == 19857);
	assert(repo.getMovieByTitle("Avatar").getTrailer() == "https://trailer1.com");
	assert(repo.getMovies().size() == 1);
}

void testService() {
	MockService service;
	Movie m("Inception", "Sci-Fi", 2010, 1000000, "https://trailer.com");

	service.addMovie(m);
	assert(service.getMovies().size() == 1);
	assert(service.getMovies()[0].getTitle() == "Inception");

	try {
		service.addMovie(m);
	}
	catch (const DuplicateMovieException&) {
		assert(true);
	}

	service.deleteMovie("Inception");
	assert(service.getMovies().size() == 0);
	try {
		service.deleteMovie("Inception");
	}
	catch (const RepositoryException&) {
		assert(true);
	}

	Movie m2("Avatar", "Sci-Fi", 2009, 2000000, "https://trailer.com");

	service.addMovie(m2);
	assert(service.getMovies().size() == 1);
	assert(service.getMovies()[0].getTitle() == "Avatar");

	service.updateMovie(Movie("Avatar", "Action", 2005, 19857, "https://trailer1.com"));
	assert(service.getMovies()[0].getGenre() == "Action");
	assert(service.getMovies()[0].getNumberOfLikes() == 19857);
	assert(service.getMovies()[0].getYearOfRelease() == 2005);
	assert(service.getMovies()[0].getTrailer() == "https://trailer1.com");
	assert(service.getMovies()[0].getTitle() == "Avatar");

	Movie m3("Trilulilu", "Action", 2005, 19857, "https://trailer1.com");
	Movie m4("Predator", "Action", 1987, 19857, "https://trailer1.com");
	service.addMovieToWatchlist("Trilulilu");
	assert(service.isMovieInWatchlist(m3) == true);
	service.addMovieToWatchlist("Predator");
	assert(service.isMovieInWatchlist(m4) == true);
	service.deleteMovieFromWatchlist("Trilulilu");
	assert(service.isMovieInWatchlist(m3) == false);
	assert(service.getWatchlist().size() == 1);
	assert(service.getWatchlist()[0].getTitle() == "Predator");

	service.addMovie(m3);
	assert(service.getMovies().size() == 2);

	auto movies_by_genre = service.getMoviesByGenre("Action");
	assert(movies_by_genre.size() == 2);

}

int test_all() {
	testMovie();
    testRepository();
    testService();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
