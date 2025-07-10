#include "bacteriaModels.h"
#include<sstream>
int bacteriaModels::rowCount(const QModelIndex& parent) const {
    (void)parent;
    return int(this->repository.getBacterias().size());
}

int bacteriaModels::columnCount(const QModelIndex& parent) const {
    (void)parent;
    return 4;
}

std::string vectorToString(const std::vector<std::string>& vec, const std::string& separator = ",") {
    std::ostringstream oss;
    for (int i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i != vec.size() - 1) {
            oss << separator;
        }
    }
    return oss.str();
}

QVariant bacteriaModels::data(const QModelIndex& index, int role) const {
    int row = index.row(), column = index.column();
    Bacteria bacteria = repository.getBacterias()[row];
    if (role == Qt::DisplayRole)
        switch (column) {
        case 0:
            return QString::fromStdString(bacteria.getName());
        case 1:
            return QString::fromStdString(bacteria.getSpecies());
        case 2:
            return QString::fromStdString(std::to_string(bacteria.getSize()));
        case 3:
            return QString::fromStdString(vectorToString(bacteria.getcausedDiseases()));

        }
    return QVariant();
}


QVariant bacteriaModels::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return "Name";
        case 1:
            return "Species";
        case 2:
            return "Size";
        case 3:
            return "Caused Diseases";
        }
    }
    return QVariant();
}

void bacteriaModels::updateData() {
    beginResetModel();
    endResetModel();
    emit this->dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

std::vector<Bacteria> bacteriaModels::getBacterias() const {
    return this->repository.getBacterias();
}

bool bacteriaModels::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role != Qt::EditRole)
        return false;

    int row = index.row();
    int column = index.column();
    auto bacterias = repository.getBacterias();
    Bacteria& bacteria = bacterias[row];

    switch (column) {
    case 0:
        bacteria.setName(value.toString().toStdString());
        break;
    case 1:
        bacteria.setSpecies(value.toString().toStdString());
        break;
    case 2:
        bacteria.setSize(value.toInt());
        break;
    case 3:
    {
        std::vector<std::string> diseases;
        std::istringstream stream(value.toString().toStdString());
        std::string disease;
        while (std::getline(stream, disease, ',')) {
            diseases.push_back(disease);
        }
        bacteria.setCausedDiseases(diseases);
    }
    break;
    default:
        return false;
    }

    repository.updateBacteria(bacteria); // Ensure the repository is updated
    emit dataChanged(index, index, { role });
    return true;
}

Qt::ItemFlags bacteriaModels::flags(const QModelIndex& index) const {
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
    if (index.isValid())
        return Qt::ItemIsEditable | defaultFlags;
    return defaultFlags;
}
