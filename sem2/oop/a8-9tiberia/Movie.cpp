#include "Movie.h"
#include "Utils.h"
#include "Validator.h"
#include <string>
#include <iostream>
#include <vector>

Movie::Movie() : title(""), genre(""), trailer(""), yearOfRelease(0), numberOfLikes(0) {}

Movie::Movie(const std::string& title, const std::string& genre, int yearOfRelease, int numberOfLikes, const std::string& trailer) :
	title{ title }, genre{ genre }, yearOfRelease{ yearOfRelease }, numberOfLikes{ numberOfLikes }, trailer{ trailer } {}

Movie::Movie(const Movie& movie) : title{ movie.title }, genre{ movie.genre }, yearOfRelease{ movie.yearOfRelease }, numberOfLikes{ movie.numberOfLikes }, trailer{ movie.trailer } {}

Movie::~Movie() {}

std::string Movie::getTitle() const
{
	return this->title;
}

std::string Movie::getGenre() const
{
	return this->genre;
}

std::string Movie::getTrailer() const
{
	return this->trailer;
}

int Movie::getYearOfRelease() const
{
	return this->yearOfRelease;
}

int Movie::getNumberOfLikes() const
{
	return this->numberOfLikes;
}

void Movie::setTitle(const std::string& title)
{
	this->title = title;
}

void Movie::setGenre(const std::string& genre)
{
	this->genre = genre;
}

void Movie::setTrailer(const std::string& trailer)
{
	this->trailer = trailer;
}

void Movie::setYearOfRelease(const int& yearOfRelease)
{
	this->yearOfRelease = yearOfRelease;
}

void Movie::setNumberOfLikes(const int& numberOfLikes)
{
	this->numberOfLikes = numberOfLikes;
}

Movie& Movie::operator=(const Movie& movie)
{
	if (this == &movie)
		return *this;	//self-assignment

	this->title = movie.title;
	this->genre = movie.genre;
	this->yearOfRelease = movie.yearOfRelease;
	this->numberOfLikes = movie.numberOfLikes;
	this->trailer = movie.trailer;
	return *this;
}

bool Movie::operator==(const Movie& movie)
{
	return this->title == movie.title && this->genre == movie.genre && this->yearOfRelease == movie.yearOfRelease && \
		this->numberOfLikes == movie.numberOfLikes && this->trailer == movie.trailer;
}

std::ostream& operator<<(std::ostream& os, const Movie& movie)
{
	os << movie.title << "," << movie.genre << "," << movie.yearOfRelease << "," << movie.numberOfLikes << "," << movie.trailer << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, Movie& movie)
{
	std::string line;
	getline(is, line);
	std::vector<std::string> result = tokenize(line, ',');

	if (result.size() == 5) {
		MovieValidator validator;
		try {
			validator.validateMovieIdentifiers(result[0], result[1], result[2], result[3], result[4]);
		}
		catch (MovieExceptions& e) {
			 throw; // rethrow
			//return is;
		}

		movie.setTitle(result[0]);
		movie.setGenre(result[1]);
		movie.setYearOfRelease(stoi(result[2]));
		movie.setNumberOfLikes(stoi(result[3]));
		movie.setTrailer(result[4]);
	}
	else {
		return is;

	}
	
	return is;
}