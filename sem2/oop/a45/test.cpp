#include <cassert>
#include "Movie.h"
#include "Repository.h"
#include "Service.h"
#include <iostream>

void testDynamicArray() {
	DynamicArray<Movie> arr;
	assert(arr.getSize() == 0);

	Movie m1("Inception", "Sci-Fi", 2010, 1000000, "https://trailer.com");
	Movie m2("Avatar", "Sci-Fi", 2009, 2000000, "https://trailer.com");
	Movie m3("The Matrix", "Sci-Fi", 1999, 1500000, "https://trailer.com");
	Movie m4("The Dark Knight", "Action", 2008, 900000, "https://trailer.com");
	Movie m5("The Godfather", "Drama", 1972, 920000, "https://trailer.com");
	Movie m6("The Shawshank Redemption", "Drama", 1994, 930000, "https://trailer.com");
	Movie m7("The Lord of the Rings: The Return of the King", "Adventure", 2003, 910000, "https://trailer.com");
	Movie m8("The Lord of the Rings: The Fellowship of the Ring", "Adventure", 2001, 880000, "https://trailer.com");
	Movie m9("The Lord of the Rings: The Two Towers", "Adventure", 2002, 900000, "https://trailer.com");
	Movie m10("The Matrix Reloaded", "Action", 2003, 780000, "https://trailer.com");
	Movie m11("The Hitman's Bodyguard", "Comedy", 2017, 760000, "https://trailer.com");

	arr.add_movie(m1);
	assert(arr.getSize() == 1);
	assert(arr[0].getTitle() == "Inception");
	arr.add_movie(m2);
	assert(arr.getSize() == 2);
	assert(arr[1].getTitle() == "Avatar");
	arr.delete_movie(0);
	assert(arr.getSize() == 1);
	assert(arr[0].getTitle() == "Avatar");

	arr.add_movie(m3);
	assert(arr.getSize() == 2);
	assert(arr[1].getTitle() == "The Matrix");
	arr.add_movie(m4);
	assert(arr.getSize() == 3);
	assert(arr[2].getTitle() == "The Dark Knight");
	arr.add_movie(m5);
	assert(arr.getSize() == 4);
	arr.add_movie(m6);
	assert(arr.getSize() == 5);
	arr.add_movie(m7);
	assert(arr.getSize() == 6);
	arr.add_movie(m8);
	assert(arr.getSize() == 7);
	arr.add_movie(m9);
	assert(arr.getSize() == 8);
	arr.add_movie(m10);
	assert(arr.getSize() == 9);
	arr.add_movie(m11);
	assert(arr.getSize() == 10);
	arr.add_movie(m1);
	assert(arr.getSize() == 11);

	Movie m12 = m5;
	arr.update_movie(0, m12);
	assert(arr[0].getTitle() == "The Godfather");
	arr.update_movie(1, m6);
	assert(arr[1].getTitle() == "The Shawshank Redemption");


	DynamicArray<Movie> movies;

	movies.add_movie(Movie("The Hitman's Bodyguard", "Comedy", 2017, 76, "https://www.youtube.com/watch?v=IpKmt4MpctM"));
	movies.add_movie(Movie("Inception", "Sci-Fi", 2010, 100, "https://www.youtube.com/watch?v=YoHD9XEInc0"));
	movies.add_movie(Movie("The Matrix", "Action", 1999, 150, "https://www.youtube.com/watch?v=vKQi3bBA1y8"));

	const DynamicArray<Movie>& constMovies = movies;

	for (int i = 0; i < constMovies.getSize(); ++i) {
		assert(constMovies[i].getTitle() == movies[i].getTitle());
	}

	DynamicArray<Movie> movies2;
	movies2.add_movie(Movie("Interstellar", "Sci-Fi", 2014, 120, "https://www.youtube.com/watch?v=zSWdZVtXT7E"));

	movies2 = movies;
	assert(movies2.getSize() == movies.getSize());
	assert(movies2[0].getTitle() == movies[0].getTitle());

	movies2 = movies2;
	assert(movies2.getSize() == movies.getSize());
	assert(movies2[0].getTitle() == movies[0].getTitle());

}

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
    Repository repo;
    Movie m("Dune", "Sci-Fi", 2021, 500000, "https://trailer.com");
    assert(repo.addMovie(m) == true);
    assert(repo.addMovie(m) == false);

	assert(repo.getMovies().getSize() == 1);
	assert(repo.getMovieByTitle("Dune").getTitle() == "Dune");
	assert(repo.getMovieByTitle("Dune").getGenre() == "Sci-Fi");
	assert(repo.getMovieByTitle("Dune").getYearOfRelease() == 2021);
	assert(repo.getMovieByTitle("Dune").getNumberOfLikes() == 500000);
	assert(repo.getMovieByTitle("Dune").getTrailer() == "https://trailer.com");
	assert(repo.getWatchlist().getSize() == 0);
	assert(repo.addMovieToWatchlist(m) == true);
	assert(repo.addMovieToWatchlist(m) == false);
	assert(repo.isMovieInWatchlist(m) == true);
	assert(repo.getWatchlist().getSize() == 1);
	assert(repo.getWatchlist()[0].getTitle() == "Dune");
	assert(repo.getWatchlist()[0].getGenre() == "Sci-Fi");
	assert(repo.getWatchlist()[0].getYearOfRelease() == 2021);
	assert(repo.getWatchlist()[0].getNumberOfLikes() == 500000);
	assert(repo.getWatchlist()[0].getTrailer() == "https://trailer.com");

	assert(repo.deleteMovieFromWatchlist("Dune") == true);
	assert(repo.deleteMovieFromWatchlist("Dune") == false);
	assert(repo.getWatchlist().getSize() == 0);
    assert(repo.deleteMovie("Dune") == true);
    assert(repo.deleteMovie("Dune") == false);

    repo.addMovie(m);
    Movie updated("Dune", "Sci-Fi", 2021, 600000, "https://new-trailer.com");
    assert(repo.updateMovie(updated) == true);
    assert(repo.getMovieByTitle("Dune").getNumberOfLikes() == 600000);
	assert(repo.getMovies().getSize() == 1);
	assert(repo.getMovieByTitle("Dune").getTrailer() == "https://new-trailer.com");
	assert(repo.isMovieInWatchlist(updated) == false);

	Movie m2("Avatar", "Sci-Fi", 2009, 2000000, "https://trailer.com");
	assert(repo.updateMovie(m2) == false);
	assert(repo.getMovies().getSize() == 1);

	assert(repo.getMovieByTitle("Matrix").getTitle() == "");
}

void testService() {
    Service service;
    Movie m("The Matrix", "Sci-Fi", 1999, 1500000, "https://trailer.com");
    assert(service.addMovieToRepository(m) == true);
    assert(service.addMovieToRepository(m) == false);

    assert(service.deleteMovieFromRepository("The Matrix") == true);
    assert(service.deleteMovieFromRepository("The Matrix") == false);

    Movie m2("Avatar", "Sci-Fi", 2009, 2000000, "https://trailer.com");
    service.addMovieToRepository(m2);
    assert(service.addMovieToWatchlist(m2) == true);
    assert(service.addMovieToWatchlist(m2) == false);
    assert(service.deleteMovieFromWatchlist("Avatar") == true);
    assert(service.deleteMovieFromWatchlist("Avatar") == false);

	Movie m3("Avatar", "Action", 2005, 19857, "https://trailer1.com");
	service.updateMovieFromRepository(m3);
	assert(service.getMovies().getSize() == 1);
	assert(service.getMoviesByGenre("Action").getSize() == 1);
	assert(service.getMovieByTitle("Avatar").getNumberOfLikes() == 19857);
	assert(service.getMoviesByGenre("Sci-Fi").getSize() == 0);
	assert(service.getWatchlist().getSize() == 0);
	assert(service.isMovieInWatchlist(m3) == false);

}

int test_all() {
   	testDynamicArray();
	testMovie();
    testRepository();
    testService();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
