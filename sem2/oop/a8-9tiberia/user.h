#pragma once
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QLineEdit>
#include "service.h"
#include "Movie.h"
#include "constant.h"

class UserWidget : public QWidget
{
	Q_OBJECT
private:
	void populateTable();
	QListWidget* movieListWidget;
	QTableWidget* movieTableWidget;

	//buttons
	QPushButton* likeButton;
	QPushButton* watchButton;
	QPushButton* nextButton;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* back;
	QPushButton* undo;
	QPushButton* redo;

	//input fields
	QLineEdit* titleInput;
	QLineEdit* genreInput;

	int currentMovieIndex = -1;
	std::vector<Movie> moviesByGenre;

	QLabel* movieDetailsLabel;

public:
	Service& service;
	UserWidget(Service& service, QWidget* parent = nullptr);
	~UserWidget();
	void showUserWindow();
	void showMovieInfo();

signals:
	void backButtonClicked();

private slots:
	void goBackToMain();
	void addToWatchlist();
	void deleteFromWatchlist();
	void likeMovie();
	void showNextMovie();
	void filterMoviesByGenre();
	void handleUndo();
	void handleRedo();
};

