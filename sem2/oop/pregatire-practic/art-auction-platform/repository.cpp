#include "repository.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

void Repository::load() {
	ifstream fu("users.txt");
	ifstream fi("items.txt");

	User u;
	while (fu >> u) {
		users.push_back(u);
	}

	Item it;
	while (fi >> it) {
		items.push_back(it);
	}
}

void Repository::saveFile() {
	ofstream fi("items.txt");
	for (auto i : items)
		fi << i << '\n';
}

void Repository::addItem(Item it) {
	items.push_back(it);
	saveFile();
}