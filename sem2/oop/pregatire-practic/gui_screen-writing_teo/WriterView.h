#pragma once

#include <QMainWindow>
#include "ui_WriterView.h"
#include "repository.h"
#include "IdeaTabelModel.h"

class WriterView : public QMainWindow
{
	Q_OBJECT

public:
	WriterView(Writer& writer, Repository& repository, IdeaTabelModel* ideaTabelModel, QWidget *parent = nullptr);
	~WriterView();

private:
	Ui::WriterViewClass ui;
	Writer& writer;
	Repository& repository;
	IdeaTabelModel* ideaTabelModel;

	void connectSignalsAndSlots();
};
