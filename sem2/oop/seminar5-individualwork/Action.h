#pragma once
#include "Song.h"
#include "Repository.h"

class Action {
public:
	Action() = default;
	virtual ~Action() = default;
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};

class ActionAdd : public Action {
private:
	Song addedSong;
	Repository &repo;
public:
	ActionAdd(const Song& song, Repository& repo) : addedSong(song), repo(repo) {}
	void executeUndo() override;
	void executeRedo() override;
};

class ActionRemove : public Action {
private:
	Song removedSong;
	Repository &repo;
public:
	ActionRemove(const Song& song, Repository& repo) : removedSong(song), repo(repo) {}
	void executeUndo() override;
	void executeRedo() override;
};

class ActionUpdate : public Action {
private:
	Song oldSong;
	Song newSong;
	Repository &repo;
public:
	ActionUpdate(const Song& oldSong, const Song& newSong, Repository& repo) : oldSong(oldSong), newSong(newSong), repo(repo) {}
	void executeUndo() override;
	void executeRedo() override;
};


