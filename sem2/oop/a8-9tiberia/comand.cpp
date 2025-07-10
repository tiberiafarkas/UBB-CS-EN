#include "comand.h"
#include <cstring>

using std::string;

AddCommand::AddCommand(Repository* movieRepo, Repository* watchRepo, Movie movie) {
	this->movieRepo = movieRepo;
	this->watchRepo = watchRepo;
	movies.push_back(movie);
}

void AddCommand::undo() {
	Movie movieToBeDeleted = movies.back();
	string title = movieToBeDeleted.getTitle();

	this->movieRepo->deleteMovie(title);

	try {
		this->watchRepo->deleteMovie(title);
	}
	catch (RepositoryException &e) {}
}

void AddCommand::redo() {
	Movie movieToBeAdded = movies.back();
	try {
		this->movieRepo->addMovie(movieToBeAdded);
	}
	catch (DuplicateMovieException& e) {
		throw e;
	}
}

DeleteCommand::DeleteCommand(Repository* movieRepo, Repository* watchRepo, Movie movie) {
	this->movieRepo = movieRepo;
	this->watchRepo = watchRepo;
	movies.push_back(movie);
}

void DeleteCommand::undo() {
	Movie movieToBeAdded = movies.back();
	string title = movieToBeAdded.getTitle();
	try {
		this->movieRepo->addMovie(movieToBeAdded);
	}
	catch (DuplicateMovieException& e) {
		throw e;
	}
}

void DeleteCommand::redo() {
	Movie movieToBeDeleted = movies.back();
	string title = movieToBeDeleted.getTitle();
	this->movieRepo->deleteMovie(title);
	try {
		this->watchRepo->deleteMovie(title);
	}
	catch (RepositoryException &e) {}
}

UpdateCommand::UpdateCommand(Repository* movieRepo, Repository* watchRepo, Movie oldMovie, Movie newMovie) {
	this->movieRepo = movieRepo;
	this->watchRepo = watchRepo;
	movies.push_back(oldMovie);
	movies.push_back(newMovie);
}

void UpdateCommand::undo() {
	Movie oldMovie = movies[0];
	string title = oldMovie.getTitle();
	this->movieRepo->updateMovie(oldMovie);
	try {
		this->watchRepo->updateMovie(oldMovie);
	}
	catch (RepositoryException& e) {}
}

void UpdateCommand::redo() {
	Movie newMovie = movies[1];
	string title = newMovie.getTitle();
	this->movieRepo->updateMovie(newMovie);
	try {
		this->watchRepo->updateMovie(newMovie);
	}
	catch (RepositoryException& e) {}
}

UndoRedoService::UndoRedoService() {}

void UndoRedoService::addCommand(Command* lastCommand) {
	undoStack.push(lastCommand);
	while (!redoStack.empty()) {
		redoStack.pop();
	}
}

void UndoRedoService::undo() {
	if (undoStack.empty()) {
		throw std::exception("No commands to undo");
	}
	Command* lastCommand = undoStack.top();
	undoStack.pop();
	lastCommand->undo();
	redoStack.push(lastCommand);
}

void UndoRedoService::redo() {
	if (redoStack.empty()) {
		throw std::exception("No commands to redo");
	}
	Command* lastCommand = redoStack.top();
	redoStack.pop();
	lastCommand->redo();
	undoStack.push(lastCommand);
}