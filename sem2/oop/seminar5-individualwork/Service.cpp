#include "Service.h"
#include <algorithm>
#include "FilePlaylist.h"
#include "RepositoryExceptions.h"

using namespace std;

void Service::addSongToRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song s{ artist, title, Duration{minutes, seconds}, source };
	this->validator.validate(s);
	this->repo.addSong(s);
	auto action = std::make_unique<ActionAdd>(s, this->repo);
	this->undoActions.push(std::move(action));

}

void Service::removeSongFromRepository(const std::string & artist, const std::string & title)
{
	Song s = this->repo.findByArtistAndTitle(artist, title);
	this->repo.removeSong(s);
	auto action = std::make_unique<ActionRemove>(s, this->repo);
	this->undoActions.push(std::move(action));
}

void Service::updateSong(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song oldSong = this->repo.findByArtistAndTitle(artist, title);
	Song newSong{ artist, title, Duration{minutes, seconds}, source };
	this->validator.validate(newSong);
	this->repo.updateSong(newSong);
	auto action = std::make_unique<ActionUpdate>(oldSong, newSong, this->repo);
	this->undoActions.push(std::move(action));
	//redo clear
}

void Service::addSongToPlaylist(const Song& song)
{
	if (this->playList == nullptr)
		return;
	this->playList->add(song);
}

void Service::addAllSongsByArtistToPlaylist(const std::string& artist)
{
	vector<Song> songs = this->repo.getSongs();
	int nSongs = static_cast<int>(count_if(songs.begin(), songs.end(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		}));

	vector<Song> songsByArtist(nSongs);
	copy_if(songs.begin(), songs.end(), songsByArtist.begin(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		});

	for (auto s : songsByArtist)
		this->playList->add(s);
}

void Service::startPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->play();
}

void Service::nextSongPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->next();
}

void Service::savePlaylist(const std::string& filename)
{
	if (this->playList == nullptr)
		return;

	this->playList->setFilename(filename);
	this->playList->writeToFile();
}

void Service::openPlaylist() const
{
	if (this->playList == nullptr)
		return;

	this->playList->displayPlaylist();
}

void Service::undo()
{
	if (this->undoActions.empty())
		throw exception("No more actions to undo!");
	auto action = std::move(this->undoActions.top());
	this->undoActions.pop();
	action->executeUndo();
	this->redoActions.push(std::move(action));
}

void Service::redo()
{
	if (this->redoActions.empty())
		throw exception("No more actions to redo!");
	auto action = std::move(this->redoActions.top());
	this->redoActions.pop();
	action->executeRedo();
	this->undoActions.push(std::move(action));
}