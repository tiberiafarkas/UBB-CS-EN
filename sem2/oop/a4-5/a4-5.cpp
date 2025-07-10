#include <iostream>
#include "Ui.h"
#include "Movie.h"
#include "test.h"

int main()
{
	test_all();

	Movie movie1 = Movie("The Hitman's Bodyguard", "comedy", 2017, 76, "https://www.youtube.com/watch?v=IpKmt4MpctM");
	Movie movie2 = Movie("The Shawshank Redemption", "drama", 1994, 93, "https://www.youtube.com/watch?v=6hB3S9bIaco");
	Movie movie3 = Movie("The Godfather", "drama", 1972, 92, "https://www.youtube.com/watch?v=sY1S34973zA");
	Movie movie4 = Movie("The Dark Knight", "action", 2008, 90, "https://www.youtube.com/watch?v=EXeTwQWrcwY");
	Movie movie5 = Movie("The Godfather: Part II", "drama", 1974, 90, "https://www.youtube.com/watch?v=qJr92K_hKl0");
	Movie movie6 = Movie("The Lord of the Rings: The Return of the King", "adventure", 2003, 91, "https://www.youtube.com/watch?v=r5X-hFf6Bwo");
	Movie movie7 = Movie("The Lord of the Rings: The Fellowship of the Ring", "adventure", 2001, 88, "https://www.youtube.com/watch?v=V75dMMIW2B4");
	Movie movie8 = Movie("The Lord of the Rings: The Two Towers", "adventure", 2002, 90, "https://www.youtube.com/watch?v=LbfMDwc4azU");
	Movie movie9 = Movie("The Matrix", "action", 1999, 87, "https://www.youtube.com/watch?v=m8e-FF8MsqU");
	Movie movie10 = Movie("The Matrix Reloaded", "action", 2003, 78, "https://www.youtube.com/watch?v=2LqzF5WauAw");

	UI ui;

	ui.service.addMovieToRepository(movie1);
	ui.service.addMovieToRepository(movie2);
	ui.service.addMovieToRepository(movie3);
	ui.service.addMovieToRepository(movie4);
	ui.service.addMovieToRepository(movie5);
	ui.service.addMovieToRepository(movie6);
	ui.service.addMovieToRepository(movie7);
	ui.service.addMovieToRepository(movie8);
	ui.service.addMovieToRepository(movie9);
	ui.service.addMovieToRepository(movie10);

	//ui.start();
}
