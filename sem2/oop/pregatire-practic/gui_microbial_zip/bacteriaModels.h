#pragma once
#include "Repository.h"
#include<QAbstractTableModel>
using namespace std;

class bacteriaModels : public QAbstractTableModel
{
private:
	Repository& repository;
public:
	bacteriaModels(Repository& repository) : repository{ repository } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	void updateData();
	vector<Bacteria>getBacterias() const;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
};