#include "IdeaTabelModel.h"

IdeaTabelModel::IdeaTabelModel(Repository& repository) : repository{ repository }
{}

int IdeaTabelModel::rowCount(const QModelIndex& parent) const
{
	return repository.getIdeas().size();
}

int IdeaTabelModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant IdeaTabelModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		int row = index.row();
		int column = index.column();

		Idea idea = repository.getIdeas()[row];

		switch (column)
		{
		case 0:
			return QString::fromStdString(idea.getDescription());
		case 1:
			return QString::fromStdString(idea.getStatus()); 
		case 2:
			return QString::fromStdString(idea.getCreator());
		case 3:
			return QString::number(idea.getAct()); 
		default:
			break;
		}
	}


	return QVariant();
}

QVariant IdeaTabelModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Description" };
			case 1:
				return QString{ "Status" };
			case 2:
				return QString{ "Creator" };
			case 3:
				return QString{ "Act" };
			default:
				break;
			}
		}
	}
	return QVariant();
}

bool IdeaTabelModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role != Qt::EditRole)
		return false;

	int row = index.row();
	int column = index.column();

	Idea& idea = this->repository.getIdeas()[row];

	switch (column)
	{
	
	case 1:
	{
		std::string status = value.toString().toStdString();
		if(status != "accepted")
			return false;
		idea.setStatus(status);
		break;
	}

	default:
		break;
	}

	emit dataChanged(index, index);

	return true;
}

Qt::ItemFlags IdeaTabelModel::flags(const QModelIndex& index) const
{
	if (index.column() != 1)
		return Qt::ItemFlags{};

	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void IdeaTabelModel::addIdea(Idea idea)
{
	repository.addIdea(idea);
	beginInsertRows(QModelIndex{}, this->rowCount(), this->rowCount()); 
	endInsertRows(); 

	emit dataChanged(this->index(0, 0), this->index(this->rowCount() - 1, this->columnCount() - 1)); 
}

void IdeaTabelModel::update()
{
	emit dataChanged(this->index(0, 0), this->index(this->rowCount() - 1, this->columnCount() - 1)); 
}

bool IdeaTabelModel::isSenior(Writer& writer)
{
	if(writer.getExpertise() == "Senior")
		return true;
	return false;
}
