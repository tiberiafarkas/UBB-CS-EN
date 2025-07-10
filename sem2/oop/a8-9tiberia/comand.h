#pragma once
#include <Repository.h>
#include <FileRepository.h>
#include <CSVRepo.h>
#include <HTMLRepo.h>
#include <vector>
#include <stack>

class Command {
protected:
	std::vector<Movie> movies;
	Repository* movieRepo;
	Repository* watchRepo;

public:
	Command() {
		this->movieRepo = nullptr;
		this->watchRepo = nullptr;
	}
	virtual void undo() = 0;
	virtual void redo() = 0;
	virtual ~Command();
};

class AddCommand : public Command {
public:
	AddCommand(Repository* movieRepo, Repository* undoRepo, Movie movie);
	void undo() override;
	void redo() override;
	~AddCommand();
};

class DeleteCommand : public Command {
public:
	DeleteCommand(Repository* movieRepo, Repository* undoRepo, Movie movie);
	void undo() override;
	void redo() override;
	~DeleteCommand();
};

class UpdateCommand : public Command {
public:
	UpdateCommand(Repository* movieRepo, Repository* undoRepo, Movie oldMovie, Movie newMovie);
	void undo() override;
	void redo() override;
	~UpdateCommand();
};

class UndoRedoService {
private:
	std::stack<Command*> undoStack;
	std::stack<Command*> redoStack;
public:
	UndoRedoService();
	void addCommand(Command* lastCommand);
	void undo();
	void redo();
	~UndoRedoService();
};


