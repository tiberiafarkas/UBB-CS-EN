#pragma once
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMessageBox>
#include "service.h"
#include "Movie.h"
#include "constant.h"

class AdminWidget : public QWidget
{
	Q_OBJECT
private:
	void populateTable();
	QListWidget* movieListWidget;
	QTableWidget* movieTableWidget;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* back;

	//input fields
	QLineEdit* titleInput;
	QLineEdit* genreInput;
	QLineEdit* yearInput;
	QLineEdit* likesInput;
	QLineEdit* trailerInput;

public:
	Service& service;
	AdminWidget(Service& service, QWidget* parent = nullptr);
	~AdminWidget();
	void showAdminWindow();

signals:
	void backButtonClicked();
	void addMovieButtonClicked();
	void deleteMovieButtonClicked();
	void updateMovieButtonClicked();

private slots:
	void goBackToMain();
	void addMovie();
	void updateMovie();
	void deleteMovie();
};
