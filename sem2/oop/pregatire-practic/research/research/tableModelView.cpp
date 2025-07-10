#include "tableModelView.h"
#include <string>

int IdeasTableView::rowCount(const QModelIndex& parent) const {
	return this->service.getIdeas().size();
}

int IdeasTableView::columnCount(const QModelIndex& parent) const {
	return 5; // Title, Description, Status, Creator, Duration
}

QVariant IdeasTableView::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int col = index.column();
	Ideea idea = this->service.getIdeas()[row];

	if (role == Qt::DisplayRole) {
		switch (col) {
		case 0:
			return QString::fromStdString(idea.getTitle());
		case 1: 
			return QString::fromStdString(idea.getDescription());
		case 2: 
			return QString::fromStdString(idea.getStatuts());
		case 3: 
			return QString::fromStdString(idea.getCreator());
		case 4: 
			return idea.getDuration();
		default: 
			return QVariant();
		}
	}
	return QVariant();
}

QVariant IdeasTableView::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0: 
				return QString("Title");
			case 1: 
				return QString("Description");
			case 2: 
				return QString("Status");
			case 3: 
				return QString("Creator");
			case 4: 
				return QString("Duration");
			default: 
				return QVariant();
			}
		}
	}
	return QVariant();
}

void IdeasTableView::addIdea(Ideea& idea) {
	beginResetModel();
	this->service.addIdeea(idea);
	endResetModel();
}

void IdeasTableView::updateIdea(Ideea& idea) {
	beginResetModel();
	int index = 0;
	for (auto& i : this->service.getIdeas()) {
		if (i.getTitle() == idea.getTitle()) {
			i = idea;
			break;
		}
		index++;
	}

	QModelIndex indexToUpdate = createIndex(index, 0);
	QModelIndex indexToUpdate2 = createIndex(index, columnCount() - 1);
	emit dataChanged(indexToUpdate, indexToUpdate2);

	endResetModel();
}

void IdeasTableView::reviseIdea(int indexOfIdea) {
	beginResetModel();
	
	Ideea& idea = this->service.getIdeas()[indexOfIdea];
	idea.setStatus("accepted");

	QModelIndex indexToUpdate = createIndex(indexOfIdea, 0);
	QModelIndex indexToUpdate2 = createIndex(indexOfIdea, columnCount() - 1);
	emit dataChanged(indexToUpdate, indexToUpdate2);

	endResetModel();
}

std::vector<Ideea> IdeasTableView::acceptedIdeas(Researcher researcher) {
	std::vector<Ideea> accepted;
	for (auto& idea : this->service.getIdeas()) {
		if (idea.getStatuts() == "accepted" && idea.getCreator() == researcher.getName()) {
			accepted.push_back(idea);
		}
	}
	return accepted;
}


