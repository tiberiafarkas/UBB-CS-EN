#include "Validator.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

MovieExceptions::MovieExceptions(std::vector<std::invalid_argument> errors) : errors{ errors } {}
MovieExceptions::MovieExceptions(std::string error) {
	this->errors.push_back(std::invalid_argument(error));
}
MovieExceptions::~MovieExceptions() {}

const char* MovieExceptions::what() const noexcept {
	return "Movie validation failed.";
}

std::vector<std::invalid_argument> MovieExceptions::returnErrors() {
	return this->errors;
}

void MovieValidator::validateMovieTitle(const std::string& title) {
	if (title == "") {
		throw std::invalid_argument("Title cannot be empty!");
	}
}

void MovieValidator::validateMovieGenre(const std::string& genre) {
	if (genre == "") {
		throw std::invalid_argument("Genre cannot be empty!");
	}
}

void MovieValidator::validateMovieYearOfRelease(const std::string& yearOfRelease) {
	if (yearOfRelease == "") {
		throw std::invalid_argument("Year of release cannot be empty!");
	}
	int year;
	try {
		year = std::stoi(yearOfRelease);
	}
	catch (const std::exception& e) {
		throw std::invalid_argument("Year of release must be a number!");
	}
	if (year < 1900 || year > 2025) {
		throw std::invalid_argument("Year of release must be between 1900 and 2023!");
	}
}

void MovieValidator::validateMovieNumberOfLikes(const std::string& numberOfLikes) {
	int likes;
	if (numberOfLikes == "") {
		throw std::invalid_argument("Number of likes cannot be empty!");
	}
	try {
		likes = std::stoi(numberOfLikes);
	}
	catch (const std::exception& e) {
		throw std::invalid_argument("Number of likes must be a number!");
	}
	if (likes < 0) {
		throw std::invalid_argument("Number of likes cannot be negative!");
	}
}

void MovieValidator::validateMovieTrailer(const std::string& trailer) {
	if (trailer == "") {
		throw std::invalid_argument("Trailer cannot be empty!");
	}
}

void MovieValidator::validateMovieIdentifiers(const std::string& title, const std::string& genre, const std::string& yearOfRelease, const std::string& numberOfLikes, const std::string& trailer) {
	std::vector<std::invalid_argument> errors;
	try {
		validateMovieTitle(title);
	}
	catch (const std::invalid_argument& e) {
		errors.push_back(e);
	}
	try {
		validateMovieGenre(genre);
	}
	catch (const std::invalid_argument& e) {
		errors.push_back(e);
	}
	try {
		validateMovieYearOfRelease(yearOfRelease);
	}
	catch (const std::invalid_argument& e) {
		errors.push_back(e);
	}
	try {
		validateMovieNumberOfLikes(numberOfLikes);
	}
	catch (const std::invalid_argument& e) {
		errors.push_back(e);
	}
	try {
		validateMovieTrailer(trailer);
	}
	catch (const std::invalid_argument& e) {
		errors.push_back(e);
	}
	if (!errors.empty()) {
		throw MovieExceptions(errors);
	}
}