#include "Action.h"

void ActionAdd::executeUndo() {
	this->repo.removeSong(this->addedSong);
}

void ActionAdd::executeRedo() {
	this->repo.addSong(this->addedSong);
}

void ActionRemove::executeUndo() {
	this->repo.addSong(this->removedSong);
}

void ActionRemove::executeRedo() {
	this->repo.removeSong(this->removedSong);
}

void ActionUpdate::executeUndo() {
	this->repo.updateSong(this->oldSong);
}

void ActionUpdate::executeRedo() {
	this->repo.updateSong(this->newSong);
}
