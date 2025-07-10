#pragma once
#include <string>

class Movie {
private:
	//Each movie has a title, a genre, a year of release, a number of likes and a trailer.
	
	std::string title;
	std::string genre;
	std::string trailer;
	int yearOfRelease;
	int numberOfLikes;

public:
	//class constructor
	Movie();
	Movie(const std::string& title, const std::string& genre, int yearOfRelease, int numberOfLikes, const std::string& trailer);

	//copy constructor
	Movie(const Movie& movie);

	//destructor
	~Movie();

	//getters
	std::string getTitle() const;
	std::string getGenre() const;
	std::string getTrailer() const;
	int getYearOfRelease() const;
	int getNumberOfLikes() const;

	//setters
	void setTitle(const std::string& title);
	void setGenre(const std::string& genre);
	void setTrailer(const std::string& trailer);
	void setYearOfRelease(const int& yearOfRelease);
	void setNumberOfLikes(const int& numberOfLikes);

	//overloading the assignment operator
	Movie& operator=(const Movie& movie);
};